#include "/home/codeleaded/System/Static/Container/Database.h"

CStr QueryLanguage_FnCStr_BOOL(void* ptr){
    return (char*)Boolean_Get(*(Boolean*)ptr);
}
CStr QueryLanguage_FnCStr_CHAR(void* ptr){
    return (char*)Number_Get(*(char*)ptr);
}
CStr QueryLanguage_FnCStr_WCHAR(void* ptr){
    return (char*)Number_Get(*(short*)ptr);
}
CStr QueryLanguage_FnCStr_BYTE(void* ptr){
    return (char*)Number_Get(*(char*)ptr);
}
CStr QueryLanguage_FnCStr_SHORT(void* ptr){
    return (char*)Number_Get(*(short*)ptr);
}
CStr QueryLanguage_FnCStr_INT(void* ptr){
    return (char*)Number_Get(*(int*)ptr);
}
CStr QueryLanguage_FnCStr_LONG(void* ptr){
    return (char*)Number_Get(*(long*)ptr);
}
CStr QueryLanguage_FnCStr_FLOAT(void* ptr){
    return (char*)Double_Get(*(float*)ptr,4);
}
CStr QueryLanguage_FnCStr_DOUBLE(void* ptr){
    return (char*)Double_Get(*(double*)ptr,4);
}
CStr QueryLanguage_FnCStr_VARCHAR(void* ptr){
    return CStr_Cpy((char*)ptr);
}

char QueryLanguage_FnCmp_BOOL(void* ptr1,void* ptr2){
    return *(Boolean*)ptr1 == *(Boolean*)ptr2;
}
char QueryLanguage_FnCmp_CHAR(void* ptr1,void* ptr2){
    return *(char*)ptr1 == *(char*)ptr2;
}
char QueryLanguage_FnCmp_WCHAR(void* ptr1,void* ptr2){
    return *(short*)ptr1 == *(short*)ptr2;
}
char QueryLanguage_FnCmp_BYTE(void* ptr1,void* ptr2){
    return *(char*)ptr1 == *(char*)ptr2;
}
char QueryLanguage_FnCmp_SHORT(void* ptr1,void* ptr2){
    return *(short*)ptr1 == *(short*)ptr2;
}
char QueryLanguage_FnCmp_INT(void* ptr1,void* ptr2){
    return *(int*)ptr1 == *(int*)ptr2;
}
char QueryLanguage_FnCmp_LONG(void* ptr1,void* ptr2){
    return *(long long*)ptr1 == *(long long*)ptr2;
}
char QueryLanguage_FnCmp_FLOAT(void* ptr1,void* ptr2){
    return *(float*)ptr1 == *(float*)ptr2;
}
char QueryLanguage_FnCmp_DOUBLE(void* ptr1,void* ptr2){
    return *(double*)ptr1 == *(double*)ptr2;
}
char QueryLanguage_FnCmp_VARCHAR(void* ptr1,void* ptr2){
    return CStr_Cmp((char*)ptr1,(char*)ptr2);
}

DB_Bool Test_Func(Vector* vec){
    for(int i = 0;i<vec->size;i++){
        void* e = *(void**)Vector_Get(vec,i);
        if(i==0 && *(short*)e==4) return DB_TRUE;
    }
    return DB_FALSE;
}

int main(){
    Database db = Database_New();
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(1,  "BOOL",     DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_BOOL,    QueryLanguage_FnCmp_BOOL    ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(1,  "CHAR",     DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_CHAR,    QueryLanguage_FnCmp_CHAR    ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(2,  "WCHAR",    DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_WCHAR,   QueryLanguage_FnCmp_WCHAR   ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(1,  "BYTE",     DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_BYTE,    QueryLanguage_FnCmp_BYTE    ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(2,  "SHORT",    DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_SHORT,   QueryLanguage_FnCmp_SHORT   ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(4,  "INT",      DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_INT,     QueryLanguage_FnCmp_INT     ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(8,  "LONG",     DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_LONG,    QueryLanguage_FnCmp_LONG    ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(4,  "FLOAT",    DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_FLOAT,   QueryLanguage_FnCmp_FLOAT   ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(8,  "DOUBLE",   DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_DOUBLE,  QueryLanguage_FnCmp_DOUBLE  ) });
    Database_Type_Push(&db,(DB_Type[]){ DB_Type_New(-1, "VARCHAR",  DB_TYPE_NOMEMBERS,QueryLanguage_FnCStr_VARCHAR, QueryLanguage_FnCmp_VARCHAR ) });

    Database_Label_Add(&db,"Hello","INT",DB_INFO_SPECIAL_PRIMARY,0);
    Database_Label_Add(&db,"World","SHORT",DB_INFO_SPECIAL_NONE,1);
    Database_Label_Add(&db,"Wtf","LONG",DB_INFO_SPECIAL_NONE,2);

    //Database_Print(&db);

    Database_Entry_Push(&db,(void*[]){ 
        (int[]){ 1 }, 
        (short[]){ 2 }, 
        (long[]){ 3 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (int[]){ 4 }, 
        (short[]){ 5 }, 
        (long[]){ 6 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (int[]){ 4 }, 
        (short[]){ 8 }, 
        (long[]){ 9 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (int[]){ 10 }, 
        (short[]){ 11 }, 
        (long[]){ 12 }, 
    });
    Database_Entry_Push(&db,(void*[]){ 
        (int[]){ 13 }, 
        (short[]){ 14 }, 
        (long[]){ 15 }, 
    });

    Database_Entry_Update(&db,1,"Hello",(int[]){ 69 });
    Database_Entry_Remove(&db,Test_Func);

    Database_Print(&db);
    Database_Write(&db,"./data/db1.alxdb");
    Database_Free(&db);

    Database_Read(&db,"./data/db1.alxdb");
    Database_Print(&db);
    Database_Free(&db);
    return 0;
}