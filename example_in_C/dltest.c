/* this is an ELF example */



#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include <ctype.h>

typedef void (*func_t) (const char *);

void
dltest (const char *s)
{
  printf ("From dltest: ");
  for (; *s; s++)
  {
    putchar (toupper (*s));
  }
  putchar ('\n');
}

main (int argc, char **argv)
{
  void *handle;
  func_t fptr;
  char *libname = "./libfoo.so";
  char **name = NULL;
  char *funcname = "foo";
  char *param = "Dynamic Loading Test";
  int ch;
  int mode = RTLD_LAZY;
  
  while ((ch = getopt (argc, argv, "a:b:f:l:")) != EOF)
  {
    switch (ch)
    {
    case 'a': /* argument. */
      param = optarg;
      break;
      
    case 'b': /* how to bind. */
      switch (*optarg)
      {
      case 'l': /* lazy */
        mode = RTLD_LAZY;
        break;

      case 'n': /* now */
        mode = RTLD_NOW;
        break;
      }
      break;

    case 'l': /* which shared library. */
      libname = optarg;
      break;

    case 'f': /* which function? */
      funcname = optarg;
    }
  }

  handle = dlopen (libname, mode);
  if (handle == NULL)
  {
    fprintf (stderr, "%s: dlopen: `%s'\n", libname, dlerror ());
    exit (1);
  }

  fptr = (func_t) dlsym (handle, funcname);
  if (fptr == NULL)
  {
    fprintf (stderr, "%s: dlsym: `%s'\n", funcname, dlerror ());
    exit (1);
  }

  name = (char **) dlsym (handle, "libname");
  if (name == NULL)
  {
    fprintf (stderr, "%s: dlsym: `libname'\n", dlerror ());
    exit (1);
  }

  printf ("Call `%s' in `%s':\n", funcname, *name);

  /* call that function with `param' */
  (*fptr) (param);

  dlclose (handle);
  return 0;
} 
