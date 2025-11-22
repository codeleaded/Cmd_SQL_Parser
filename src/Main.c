#include "/home/codeleaded/System/Static/Library/QueryLanguage.h"

int main(int argc,char** argv){
    //if(argc==1){
    //    printf("Expected a Script!\n");
    //    exit(1);
    //}

    CStr path = Files_cwd();
    CStr target = CStr_Concat(path,"/data");
    CStr_Free(&path);
    //printf("Target: %s\n",target);
    
    QueryLanguage ql = QueryLanguage_New(target);
    CStr_Free(&target);

    //QueryLanguage_Load(&ql,"./Database1.alxdb","Database1");

    //QueryLanguage_InterpretLine(&ql,"CREATE db2;");
    //QueryLanguage_Print(&ql);
    //QueryLanguage_InterpretLine(&ql," -- Hello World\nLOAD db1; /* WOw \n ok */ LOAD db2;");

    QueryLanguage_InterpretScript(&ql,"./code/Main.alxql");//argv[1]
    QueryLanguage_Free(&ql);

    return 0;
}