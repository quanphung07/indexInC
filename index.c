#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
typedef struct word
{
    char *word_name;
    int nums;
    int line_index[30];
} word;
void readFile(char *fileName, char **index_sentences, int *line)
{
    FILE *fp = fopen(fileName, "r");
    char *str;
    *line = 0;
    int i = 0;
    while (fgets(index_sentences[i], 200, fp))
    {
        index_sentences[i][strlen(index_sentences[i]) - 2] = '\0';
        for (int j = 0; j <= strlen(index_sentences[i]); j++)
        {
            if (index_sentences[i][j] >= 65 && index_sentences[i][j] <= 90)
            {
                index_sentences[i][j] = index_sentences[i][j] + 32;
            }
        }
        i++;
        *line += 1;
    }

    fclose(fp);
}
int check_stopw(char *word, char **index_stopwords, int *num_stopw)
{
    int check = 0;
    for (int i = 0; i < *num_stopw; i++)
    {
        if (strcmp(word, index_stopwords[i]) == 0)
        {
            check = 1;
        }
        else
        {
            continue;
        }
    }
    if (check != 0)
    {
        return 1;
    }
    return 0;
}
void read_file_stopw(char *fileName, char **index_stopwords, int *num_stopw)
{
    FILE *fp = fopen(fileName, "r");

    *num_stopw = 0;
    int i = 0;
    while (fscanf(fp, "%s", index_stopwords[i]))
    {

        i++;
        *num_stopw += 1;
    }
    // for(int i=0;i<*num_stopw;i++)
    // {
    //     printf("%s %d \n",index_stopwords[i],strlen(index_stopwords[i]));
    // }
    fclose(fp);
}
void *word_delete_character(char *word)
{
    int length = strlen(word);
    char *word_fixed=malloc(sizeof(char)*15);
    //int count;
    int dot_times = 0;
    int count;
    int dot_position=0;

    for (count = 0; count < length; count++)
    {


        if(word[count] == '.') 
        {
            dot_position=count;
            dot_times++;
        }   

        // if (word[count] == '.')
        // {
        //     if (count + 1 == length)
        //     {
        //         dot_times++;
        //         break;
        //     }
        //     else
        //     {
        //         dot_times++;
        //     }
        // }
    }
 // printf("%s %d %d",word,dot_position,dot_times);
  if(dot_times==1)
  {
      strncpy(word_fixed,word,dot_position);
       return word_fixed;
       
  }else
  {return word;}
  
    // if (dot_times == 1)
    // {
    //     for (int i = 0; i < count; i++)
    //     {
    //         word_fixed[i] = word[i];
    //     }
    //     return word_fixed;
    // }
    // else
    // {
    //     return word;
    // }
}
void word_process(char ***index_words, int *line)
{
     char *word ;
    for (int i = 0; i < *line; i++)
    {

        
        for (int j = 0; j < 20; j++)
        {
             word =malloc(sizeof(char)*15);

           // printf("%s %d\n",index_words[i][j],strlen(index_words[i][j]));
         
             word= word_delete_character(index_words[i][j]);
           
            
            strcpy(index_words[i][j],word);

           
           
        }
        free(word);
        
    }
}
void devide_word_by_line(char **index_sentences, char ***index_words, char **index_stopwords, int *line, int *num_stopw)
{
    char delim[3] = " ,";
    char *token;
    int j;
    for (int i = 0; i < *line; ++i)
    {
        j = 0;
        token = strtok(index_sentences[i], delim);
        while (token != NULL)
        {
            //printf("%s\n",token);
            if (check_stopw(token, index_stopwords, num_stopw) == 0)
            {

                strcpy(index_words[i][j], token);
                j++;
            }

            token = strtok(NULL, delim);
        }
    }
   // printf("%s\n",index_words[3][7]);
    
}
void word_reset(word* word)
{
    word->word_name=malloc(sizeof(char)*15);
     memset(word->word_name, 0, 15);
    word->nums = 0;
    for (int j = 0; j < 30; j++)
    {
        word->line_index[j] = 0;
    }
}
//kiem tra xem tu da ton tai trong word_list chua
int check_word_exist(word word_list[],char *word)
{
    int check=0;
    for(int i=0;i<100;i++)
    {
        if(strcmp(word_list[i].word_name,word)==0)
        {
            check=1;
        } 
    }
    if(check==0)
    {
        return 1;
    }
    return 0;
    
}
//tim index cua tu trong word list
int find_word_in_word_list(word word_list[],char *word)
{
    int index=0;
    for(int i=0;i<100;i++)
    {
        if(strcpy(word_list[i].word_name,word)==0)
        {
           index=i;
           break;
        }
    }
    return index;
}
//tao ra list cac tu cung cac chi muc
void word_list_init(char ***index_words,word word_list[],int *line,int *total_words)
{
    int index=0;
    char *str;
    *total_words=0;
     word new_word;
 for(int i=0;i<*line;i++)
 {
     for(int j=0;j<25;j++)
     {
         str=malloc(sizeof(char)*15);
         str=index_words[i][j];
        //  if(check_word_exist(word_list,str)==0)
        //  {
        //      int word_index=find_word_in_word_list(word_list,str);
        //      word_list[word_index].nums++;
        //       int k = 0;
        //      while (word_list[word_index].line_index[k] != 0)
        //     {
        //      k++;
        //      }
        //         word_list[word_index].line_index[k] =i;

        //  }
        //  else
        //  {
        
         word_reset(&new_word);
         strcpy(new_word.word_name,str);
       //  printf("%s ",new_word.word_name);
         new_word.nums++;
         int k = 0;
         while (new_word.line_index[k] != 0)
            {
                k++;
            }
        new_word.line_index[k] =i;
        word_list[index]=new_word;
        *total_words+=1;
        index++;
        free(str);

     }
     printf("\n");
     
 }

}

void main()
{
    char **index_sentences;
    int line;
    int num_stopw;
    int total_words;
    word word_list[200];
    
    index_sentences = (char **)malloc(sizeof(char *) * 15);
    for (int i = 0; i < 10; i++)
    {
        index_sentences[i] = (char *)malloc(sizeof(char) * 250);
    }
    char **index_stopwords;

    index_stopwords = (char **)malloc(sizeof(char *) * 20);
    for (int i = 0; i < 20; i++)
    {
        index_stopwords[i] = (char *)malloc(sizeof(char) * 20);
    }
    char ***index_words;
    index_words = (char ***)malloc(sizeof(char **) * 10);
    for (int i = 0; i < 10; i++)
    {
        index_words[i] = (char **)malloc(sizeof(char *) * 30);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            index_words[i][j] = (char *)malloc(sizeof(char) * 15);
        }
    }

    

    readFile("vanban.txt", index_sentences, &line);
    read_file_stopw("stopw.txt", index_stopwords, &num_stopw);
    devide_word_by_line(index_sentences, index_words, index_stopwords, &line, &num_stopw);
    word_process(index_words, &line);
    word_list_init(index_words,word_list,&line,&total_words);
//    for(int i=0;i<total_words;i++)
//    {
//        if(word_list[i].nums!=0)
//        printf("%s ",word_list[i].word_name);
//    }

 // printf("%s",index_words[3][7]);
//    char *word=malloc(sizeof(char)*15);
//    word=word_delete_character(index_words[3][7]);
//  printf("%s",word);

    //   for (int i = 0; i < 20; i++)
    //   {

    //        printf("%s %ld\n",index_words[9][i],strlen(index_words[9][i]));
    //   }
    // for(int i=0;i<10;i++)
    // {
    //     for(int j=0;j<30;j++)
    //     {
    //        printf("%s %d\n",index_words[i][j],strlen(index_words[i][j]));
    //     }
    // }
}