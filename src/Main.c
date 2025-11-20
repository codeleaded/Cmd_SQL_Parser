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
    Database_Write(&db,"./data/db1.alxdb");
    Database_Free(&db);

    Database_Read(&db,"./data/db1.alxdb");
    Database_Print(&db,Print_Func);
    Database_Free(&db);
    return 0;
}