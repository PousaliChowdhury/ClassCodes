#include<stdio.h>
#include<stdlib.h>
void main()
{
 int a[20],c[20],d[20],aux[20],r,i,j,len,in,flag,choice,key;
 printf("\n ENTER THE SIZE OF DATA WORD :");
 scanf("%d",&len);
 printf("\n ENTER THE DATA WORD ONE BY ONE:");
 for(i=0; i<len; i++)
 scanf("%d",&a[i]);
 printf("\n ENTER THE NUMBER OF REDUNDANT BITS :");
 scanf("%d",&r);
 printf("\n ENTER THE DIVISOR OR CRC GENERATOR ONE BY ONE:");
 for(i=0; i<(r+1); i++)
 scanf("%d",&d[i]);
 for(i=0; i<(len+r); i++)
 {
 if(i<len)
 c[i]=a[i];
 else
 c[i]=0;
 }
 printf("\n\n ... GENERATOR MODULE ... \n");
 printf("\n\n THE INTERMEDIATE CODE WORD IS : ");
 for(i=0; i<(len+r); i++)
 printf("%d ",c[i]);
 for(i=0; i<(len+r); i++)
 aux[i]=c[i];
 for(i=0; i<len; i++)
{
 in=1; /* if second last bit is one */
 if(c[i]==1){
for(j=i+1; j<(i+len); j++)
{
 c[j]=c[j]^d[in];
 in++;
}
 }
 else{
for(j=i+1; j<(i+len); j++)
 c[j]=c[j]^0; /* if second last bit is zero */
 }
 }
 printf("\n\n THE REMAINDER AFTER DIVISION IS : ");
 for(i=len; i<(len+r); i++)
 printf("%d ",c[i]);
 printf("\n\n SENDER CODE WORD : ");
 for(i=0; i<(len+r); i++){
 if(i<len) c[i]=aux[i];
 printf("%d ",c[i]);
 }
 printf("\n\n\n PRESS 1 IF YOU WANT TO CHANGE A BIT OR 0 TO CONTINUE : ");
 scanf("%d",&choice);
 if(choice==1){
 printf("\n\n ENTER THE BIT YOU WANT TO CHANGE :");
 scanf("%d",&key);
 for(i=0; i<(len+r); i++){
 if(i==(key-1)){
 if(c[key-1]==0) c[key-1]=1;
 else c[key-1]=0;
 }
 }
 printf("\n\n\n CODE WORD AFTER ERROR : ");
 for(i=0; i<(len+r); i++)
 printf("%d ",c[i]);
 }
 else
 printf("\n\n\n NO ERROR INSERTED IN CODE WORD... ");
 printf("\n\n\n\n ... CHECKER MODULE ... ");
 for(i=0; i<len; i++){
 in=1;
 if(c[i]==1){
 for(j=i+1; j<(i+len); j++){
 c[j]=c[j]^d[in];
 in++;
 }
 }
 else{
 for(j=i+1; j<(i+len); j++)
 c[j]=c[j]^0; }
 }
 printf("\n\n\n THE SYNDROME ARRAY IS : ");
 for(i=len; i<(len+r); i++)
 printf("%d ",c[i]);
 flag=0;
 for(i=len; i<(len+r); i++){
 if(c[i]!=0){
 flag=1;
 break;
 }
 }
 if(flag==1)
 printf("\n\n\n ERROR DETECTED !!!");
 else
 printf("\n\n\n NO ERROR FOUND");
}