#include "/home/codeleaded/System/Static/Library/QueryLanguage.h"

#define TOKEN_CUSTOM_SELECT      TOKEN_START+0
#define TOKEN_CUSTOM_FROM        TOKEN_START+1

void Print_Func(void* ptr,DB_Info* info){
    if(info->size==1) printf("(char) %d",*(char*)ptr);
    if(info->size==2) printf("(short) %d",*(short*)ptr);
    if(info->size==4) printf("(int) %d",*(int*)ptr);
    if(info->size==8) printf("(long) %ld",*(long*)ptr);
}
DB_Bool Test_Func(Vector* vec){
    for(int i = 0;i<vec->size;i++){
        void* e = *(void**)Vector_Get(vec,i);
        if(i==0 && *(short*)e==4) return DB_TRUE;
    }
    return DB_FALSE;
}

int main(int argc,char** argv){

    if(argc==1){
        printf("Expected a Script!\n");
        exit(1);
    }

    QueryLanguage ql = QueryLanguage_New();

    //QueryLanguage_Load(&ql,"./Database1.alxdb","Database1");

    //QueryLanguage_InterpretLine(&ql,"CREATE db2;");
    //QueryLanguage_Print(&ql);
    //QueryLanguage_InterpretLine(&ql," -- Hello World\nLOAD db1; /* WOw \n ok */ LOAD db2;");

    QueryLanguage_InterpretScript(&ql,argv[1]);

    QueryLanguage_Free(&ql);

    return 0;
}