/* Faker 1.0                                               */
/*                                                         */
/* This code is Public Domain                              */
/* compiled and tested with emx09a/fix 04                  */
/*                                                         */
/* Created by Radim Kolar 2:423/66.111                     */
/*   SysOp of Dark side of Avalon                          */
/*                                                         */
/* What it is, and how-to-run:                             */
/*  If want to know parameters parsed to some program, then*/
/*   Faker is all what you need.                           */
/* I want to know something about ppp.exe, then:           */  
/*                                                         */
/* Instalation and setup:                                  */
/*                                                         */
/* 1) rename ppp.exe to something else .EXE and leave it in*/
/* original directory or move it simply out from PATH      */
/* 2) rename fake.exe to ppp.exe, and place it to original */
/* ppp.exe directory                                       */
/* 3) in root of drive C: create ascii file fake.run with  */
/* name of renamed ppp.exe on first line (or full path to  */
/* old ppp.exe)                                            */
/* 4) Now you are ready, simply run SLIPPM, this runs fake */
/* and fake runs old ppp.                                  */
/* 5) Look into file fake.it (located in root direcory on C*/
/* drive and enjoy !                                       */
/*                                                         */
/* Note: if fake.run not exists, fake only records para-   */
/*   meters into fake.it and returns with errolevel 0      */
/* Note2: if fake cannot open fake.it, all infos are prin- */
/*   ted to stdout                                         */
/* Rev. History:                                           */
/* 24.8.1995      Log date+time added                      */
/*                hard-coded output filename c:\fake.it    */
/*                log file is now opened in append mode    */
/*                if open fake.it fails, report to stdout  */
/*                Now also runs with program in c:\fake.run*/
/*                   with the same parameters!             */
/*                If run fails, returns errorlevel 0       */
/*                if not fails returns the errorlevel, re- */
/*                   turned by programm in fake.run !      */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <process.h>

int main(int n,char *a[])
{
 int i;
 int rc=0; /* default rc */
 char frun[257];
 FILE *out,*cfg;
 char *cas;
 time_t sec=time(NULL);
 cas=ctime(&sec);
 strcpy(frun,"");
 fprintf(stdout,"Faker 1.0 StdOut!\n");
 fprintf(stderr,"Stderr!");
 out=fopen("c:\\fake.it","at");
 cfg=fopen("C:\\fake.run","rt");
 if (cfg!=NULL) { i=fscanf(cfg,"%s",frun);
                  if(i==EOF) strcpy(frun,"");
                  fclose(cfg);
                }  
 if(out==NULL) { printf("\aError opening fake.it file!");
                 out=stdout;}
 
 fprintf(out,"Faker 1.0 started at %s",cas);
 fprintf(out,"Arguments count n=%d\n\n",n-1);
 for(i=0;i<n;i++)
   fprintf(out,"%d = %s\n",i,a[i]);
 if (strlen(frun)>0) {
                      fprintf(out,"Executing : %s \n",frun);
                      i=spawnv(P_WAIT|P_DEFAULT,frun,a);
                      if(i==-1) fprintf(out,"Execute failed, check fake.run !\n");
                                else { fprintf(out,"Returned with errorlevel %d\n",i);
                                       rc=i;}
                     }
 fprintf(out,"---Faker 1.0 done, ");
 sec=time(NULL);
 cas=ctime(&sec);
 fprintf(out,"%s\n",cas);
 fclose(out);
 return rc;
}

