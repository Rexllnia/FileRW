int SearchInFile(char *input_str,int n,char *path)
{
    FILE *fp;
    int i=1;
    int k=1;
    int flag=1;
    char *str=(char*)malloc(n);
    fp = fopen(path, "r");
    while (strcmp(input_str,str)!=0)
    {
        //  fgets(str,n,fp);
        
        fseek(fp,i++,SEEK_SET);
        
        fread(str,n-1,1,fp);


        
        if(str[0]=='\n')
        {
            flag=!flag;
        }
        if(flag==1)
        {
            k++;
        }
        


        str[n-1]='\0';
        
         
    }
    fclose(fp);
    return k;

}

void InsertInFile(char *source,char * dest,long place)
{
    FILE *source_fp,*dest_fp,*temp_fp;
    char ch;
    int i=1;
    int j=0;
    source_fp=fopen(source,"r");
    dest_fp=fopen(dest, "r");
    temp_fp=fopen("temp.txt","w");

    char buf[101];
    while(1)
    {
        if((j+=100)>place)
        {
            fread(buf,place%100,1,dest_fp);
            buf[place%100]='\0';
            fwrite(buf,place%100,1,temp_fp);
            printf("%s",buf);
            break;
        }
        fread(buf,100,1,dest_fp);
        buf[100]='\0';
        fwrite(buf,100,1,temp_fp);
        printf("%s",buf);
    }



    fclose(temp_fp);
    temp_fp=fopen("temp.txt","r+");
    fseek(temp_fp,0,SEEK_END);
    while(ch=fgetc(source_fp))//插入的内容插入到临时文件中
    {

        if(feof(source_fp))
        {
            
            break;
        }
        fputc(ch,temp_fp);
        
    }
    while(ch=fgetc(dest_fp))//后部分插入到临时文件中
    {
        
        if(feof(dest_fp))
        {
            
            break;
        }
        fputc(ch,temp_fp);
        
    }
    fclose(source_fp);
    fclose(dest_fp);
    fclose(temp_fp);
    remove(dest);
    rename("temp.txt",dest);
}
