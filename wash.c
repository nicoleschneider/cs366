// This is my code
// Nicole Schneider
// cs366

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <string.h>
#include <utime.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLEN 100

void catTerminal();
int duplicate();
int renameFile();
int unlinkFile();
int truncateFile();
int append();
int lastBytes();
int modifyPermissions();
int setTime();

int main (int argc, char* argv[])
{
  char buf[MAXLEN][MAXLEN];
  char command;
  int fileCount = argc - 1;  

  int i;
  for(i = 0; i < fileCount; i++)
    strcpy(buf[i], argv[i+1]);

  int currentFile = 0;
  while(currentFile < fileCount && command != 'q')
  {
    printf("\nFile: %s Command: ", buf[currentFile]);
    scanf(" %c", &command);

    if(command == 'c')
      catTerminal(buf[currentFile]); // list current file to terminal
    else if(command == 'd')
      duplicate(buf[currentFile]); // copy current file
    else if(command == 'r')
      renameFile(buf[currentFile]); // rename current file
    else if(command == 'u')
      unlinkFile(buf[currentFile]); // delete current file
    else if(command == 't')
      truncateFile(buf[currentFile]); // truncate file to length zero
    else if(command == 'a')
      append(buf[currentFile]); // append current file to another file
    else if(command == 'l')
      lastBytes(buf[currentFile]); // display last 100 bytes of current file
    else if(command == 'm')
      modifyPermissions(buf[currentFile]); // change file's access permissions
    else if(command == 'x')
      setTime(buf[currentFile]); // change file's access time to current time
    else if(command == 'n')
      currentFile++; // move on to next file 
 
  }
  printf("Thanks for using this program!\n");
  return 0;
}

// 'c'
// print file name to terminal
void catTerminal(char* file)
{
  FILE* terminal = fopen("/dev/tty", "w");
  fprintf(terminal, "Current file is: %s\n", file);
}

// 'd'
// copy file
int duplicate(char* file)
{
  char current;
  char dest[100];

  printf("Enter the name of the new file: ");
  scanf("%s", dest);

  FILE* new = fopen(dest, "a");
  FILE* orig = fopen(file, "w+");
  if((new == NULL) || (orig == NULL))
  {
    perror("fopen");
    exit(0);
  }
  while((current = fgetc(orig)) != EOF)
    fputc(current, new);
  fclose(orig);
  fclose(new);

  return 0;
}

// 'r'
// rename current file
int renameFile(char* file)
{
  char newName[100];
  printf("Enter a new file name: ");
  scanf("%s", newName);
  if(rename(file, newName) != 0)
  {
    perror("rename");
    exit(0);
  }
  return 0;
}

// 'u'
// delete the current file
int unlinkFile(char* file)
{
  if(remove(file) == -1)
  {
    perror("remove");
    exit(0);
  }
  return 0;
}

// 't'
// truncate current file to length zero
int truncateFile(char* file)
{
  if(truncate(file, 0) == -1)
  {
    perror("truncate");
    exit(0);
  }
  return 0;
}

// 'a'
// append file to another file
int append(char* file)
{
  char current;
  char dest[100];

  printf("Enter the name of the new file: ");
  scanf("%s", dest);

  FILE* new = fopen(dest, "a");
  FILE* orig = fopen(file, "r");
  if((new == NULL) || (orig == NULL))
  {
    perror("fopen");
    exit(0);
  }
  while((current = fgetc(orig)) != EOF)
    fputc(current, new);
  fclose(orig);
  fclose(new); 
  return 0;
}

// 'l'
// display last 100 bytes of current file
int lastBytes(char* file)
{
  int numBytes = 100;
  FILE *f = fopen(file, "r");
  if(f == NULL)
  {
    perror("fopen");
    exit(0);
  }
  char byteHolder [numBytes];

\  fseek(f, -1*numBytes, SEEK_END);
  fread(byteHolder, 1, numBytes, f);
  byteHolder[(sizeof byteHolder) - 1] = 0;
  printf("Last %d bytes are:\n%s", numBytes, byteHolder);
  fclose(f);
  return 0;
}

// 'm'
// change permissions
int modifyPermissions(char* file)
{
  int mode;
  printf("Please enter integer for mode (like 0777, 0755, etc.): ");
  scanf("%i", &mode);
  chmod(file, mode);
  return 0;
}

// 'x'
// change access time to current time
int setTime(char* file)
{
  utime(file, NULL);
  return 0;
}
