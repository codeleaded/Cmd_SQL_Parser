#include "/home/codeleaded/System/Static/Library/AlxParser.h"
#include "/home/codeleaded/System/Static/Container/Database.h"

void Print_Func(void* ptr,DB_Info* info){
    if(info->size==1) printf("(char) %d\t",*(char*)ptr);
    if(info->size==2) printf("(short) %d\t",*(short*)ptr);
    if(info->size==4) printf("(int) %d\t",*(int*)ptr);
    if(info->size==8) printf("(long) %ld\t",*(long*)ptr);
}

DB_Bool Test_Func(Vector* vec){
    for(int i = 0;i<vec->size;i++){
        void* e = *(void**)Vector_Get(vec,i);
        if(i==0 && *(short*)e==4) return DB_TRUE;
    }
    return DB_FALSE;
}

#define TOKEN_CUSTOM_HELLO      TOKEN_START+0
#define TOKEN_CUSTOM_WORLD      TOKEN_START+1

#define TOKEN_CUSTOM_ASS        TOKEN_START+2
#define TOKEN_CUSTOM_ADD        TOKEN_START+3
#define TOKEN_CUSTOM_SUB        TOKEN_START+4
#define TOKEN_CUSTOM_NEG        TOKEN_START+5
#define TOKEN_CUSTOM_DEC        TOKEN_START+6

int main(){

    Database db = Database_Make(3,
        (DB_Type[]){ 
            DB_Type_New(2,"short",NULL),
            DB_Type_New(4,"int",NULL),
            DB_Type_New(8,"long",NULL)
        },
        (char*[]){ "Hello","World","Wtf" }
    );

    //Database_Print(&db);

    Database_Entry_Push(&db,(void*[]){ 
        (short[]){ 1 }, 
        (int[]){ 2 }, 
        (long[]){ 3 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (short[]){ 4 }, 
        (int[]){ 5 }, 
        (long[]){ 6 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (short[]){ 4 }, 
        (int[]){ 8 }, 
        (long[]){ 9 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (short[]){ 10 }, 
        (int[]){ 11 }, 
        (long[]){ 12 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (short[]){ 13 }, 
        (int[]){ 14 }, 
        (long[]){ 15 }, 
    });

    Database_Entry_Update(&db,1,"World",(int[]){ 69 });

    Database_Entry_Remove(&db,Test_Func);

    Database_Print(&db,Print_Func);

    Database_Write(&db,"./Database1.alxql");

    Database_Free(&db);

    Database_Read(&db,"./Database1.alxql");

    Database_Print(&db,Print_Func);

    Database_Free(&db);


    KeywordMap kwm = KeywordMap_Make((KeywordRP[]){
        KeywordRP_New("Hello",TOKEN_CUSTOM_HELLO),
        KeywordRP_New("World",TOKEN_CUSTOM_WORLD),
        KeywordRP_End()
    });
    OperatorMap om = OperatorMap_Make((OperatorRP[]){
        OperatorRP_Make((TT_Type[]){ TOKEN_EQUAL_SIGN,TOKEN_INITLISTEND },                  TOKEN_CUSTOM_ASS,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_PLUS_SIGN,TOKEN_INITLISTEND },                   TOKEN_CUSTOM_ADD,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_INITLISTEND },                  TOKEN_CUSTOM_SUB,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_INITLISTEND },                  TOKEN_CUSTOM_NEG,0),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,TOKEN_INITLISTEND }, TOKEN_CUSTOM_DEC,0),
        OperatorRP_End()
    });
    ReseterMap rsm = ReseterMap_Std();
    
    Parser p = Parser_New();

    Parser_Parse_cstr(&p,"a = --a - 1 + (-1) - (--a);");
    Parser_Print(&p);
    Parser_TF_Std(&p);
    Parser_TF_KW(&p,&kwm);
    Parser_Print(&p);
    Parser_TF_OPS(&p,&om,&rsm);
    Parser_Print(&p);
    
    Parser_Free(&p);
    ReseterMap_Free(&rsm);
    OperatorMap_Free(&kwm);
    KeywordMap_Free(&kwm);

    return 0;
}