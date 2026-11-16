#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 1024
#define MAX_VARS 26

double vars[MAX_VARS];
int var_used[MAX_VARS] = {0};
char history[100][MAX];
int hist_count = 0;

double values[MAX];
char ops[MAX];
int valTop, opsTop;

void pushVal(double v){ values[++valTop]=v; }
double popVal(){ return values[valTop--]; }
void pushOp(char o){ ops[++opsTop]=o; }
char popOp(){ return ops[opsTop--]; }
char peekOp(){ return ops[opsTop]; }

int precedence(char op){
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/'||op=='%') return 2;
    if(op=='^') return 3;
    return 0;
}
int isOperator(char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='%'; }

double applyOp(double a, double b, char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': if(b==0){printf("Error: /0\n"); return 0;} return a/b;
        case '^': return pow(a,b);
        case '%': return fmod(a,b);
    }
    return 0;
}

double evaluate(char* expr);

double getVarValue(char name){
    name = tolower(name);
    if(name>='a' && name<='z' && var_used[name-'a']) return vars[name-'a'];
    return 0;
}

double evaluate(char* expr){
    valTop=-1; opsTop=-1;
    for(int i=0; i<strlen(expr); i++){
        if(expr[i]==' ') continue;
        if(isdigit(expr[i])||expr[i]=='.'){
            char numStr[64]; int j=0;
            while(i<strlen(expr) && (isdigit(expr[i])||expr[i]=='.')) numStr[j++]=expr[i++];
            numStr[j]='\0'; i--;
            pushVal(atof(numStr));
        } else if(isalpha(expr[i]) && isalpha(expr[i+1])){ // function
            char func[16]; int j=0;
            while(isalpha(expr[i])) func[j++]=expr[i++];
            func[j]='\0'; i--;
            int start=i+2, end=start, par=1;
            while(expr[start-1]!='(') start++; // find (
            // find inside
            start=i+1; while(expr[start]!='(') start++; start++;
            end=start; par=1;
            while(par!=0 && expr[end]!='\0'){ if(expr[end]=='(')par++; if(expr[end]==')')par--; if(par!=0)end++; }
            char inside[256]; strncpy(inside, expr+start, end-start); inside[end-start]='\0';
            double v=evaluate(inside);
            if(strcmp(func,"sqrt")==0) pushVal(sqrt(v));
            else if(strcmp(func,"sin")==0) pushVal(sin(v));
            else if(strcmp(func,"cos")==0) pushVal(cos(v));
            else if(strcmp(func,"log")==0) pushVal(log10(v));
            else if(strcmp(func,"ln")==0) pushVal(log(v));
            i=end;
        } else if(isalpha(expr[i])){ // variable
            pushVal(getVarValue(expr[i]));
        } else if(expr[i]=='(') pushOp(expr[i]);
        else if(expr[i]==')'){
            while(opsTop!=-1 && peekOp()!='('){ double b=popVal(), a=popVal(); pushVal(applyOp(a,b,popOp())); }
            popOp();
        } else if(isOperator(expr[i])){
            // handle negative number
            if(expr[i]=='-' && (i==0 || expr[i-1]=='(' || isOperator(expr[i-1]))){
                char numStr[64]; int j=0; numStr[j++]=expr[i++];
                while(i<strlen(expr) && (isdigit(expr[i])||expr[i]=='.')) numStr[j++]=expr[i++];
                numStr[j]='\0'; i--;
                pushVal(atof(numStr));
            } else {
                while(opsTop!=-1 && precedence(peekOp())>=precedence(expr[i])){
                    double b=popVal(), a=popVal(); pushVal(applyOp(a,b,popOp()));
                }
                pushOp(expr[i]);
            }
        }
    }
    while(opsTop!=-1){ double b=popVal(), a=popVal(); pushVal(applyOp(a,b,popOp())); }
    return values[0];
}

int main(){
    char expr[MAX];
    printf("=== PRO Calculator v2 ===\nSupports: variables, history, sqrt sin cos log ln\nCommands: history, vars, clear, exit\n");
    // load history
    FILE *f=fopen("calc_history.txt","r");
    if(f){ while(fgets(history[hist_count],MAX,f) && hist_count<100) hist_count++; fclose(f); }

    while(1){
        printf("\n>> ");
        if(!fgets(expr,MAX,stdin)) break;
        expr[strcspn(expr,"\n")]=0;
        if(strlen(expr)==0) continue;
        if(strcmp(expr,"exit")==0) break;
        if(strcmp(expr,"history")==0){
            for(int i=0;i<hist_count;i++) printf("%d: %s",i+1,history[i]);
            continue;
        }
        if(strcmp(expr,"vars")==0){
            for(int i=0;i<26;i++) if(var_used[i]) printf("%c = %.6g\n",'a'+i,vars[i]);
            continue;
        }
        if(strcmp(expr,"clear")==0){ system("clear"); continue; }

        // save history
        if(hist_count<100){ strcpy(history[hist_count++], expr); strcat(history[hist_count-1],"\n"); }
        FILE *hf=fopen("calc_history.txt","a"); if(hf){ fprintf(hf,"%s\n",expr); fclose(hf); }

        // check variable assignment: x=5+3
        char *eq=strchr(expr,'=');
        if(eq){
            char varName=tolower(expr[0]);
            double res=evaluate(eq+1);
            vars[varName-'a']=res; var_used[varName-'a']=1;
            printf("%c = %.6g\n",varName,res);
        } else {
            double result=evaluate(expr);
            printf("= %.6g\n",result);
        }
    }
    return 0;
}