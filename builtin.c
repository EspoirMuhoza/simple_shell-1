#include "shell.h"

/* Exit the shell with a given status */
int _myexit(info_t *info)
{
  int status;

  /* Check if there is an exit argument */
  if (info->argv[1])
  {
    /* Convert the argument to an integer */
    status = _erratoi(info->argv[1]);
    /* If the argument is invalid, print an error and return */
    if (status == -1)
    {
      info->status = 2;
      print_error(info, "Illegal number: ");
      _eputs(info->argv[1]);
      _eputchar('\n');
      return (1);
    }
    /* Set the error number to the argument value */
    info->err_num = status;
    /* Return -2 to indicate exit */
    return (-2);
  }
  /* If there is no argument, set the error number to -1 */
  info->err_num = -1;
  /* Return -2 to indicate exit */
  return (-2);
}

/* Change the current directory of the process */
int _mycd(info_t *info)
{
  char *s, *dir, buffer[1024];
  int ret;

  /* Get the current working directory */
  s = getcwd(buffer, 1024);
  if (!s)
    _puts("TODO: >>getcwd failure emsg here<<\n");

  /* If there is no argument, change to the home directory */
  if (!info->argv[1])
  {
    dir = _getenv(info, "HOME=");
    if (!dir)
      ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
    else
      ret = chdir(dir);
  }
  /* If the argument is "-", change to the previous directory */
  else if (_strcmp(info->argv[1], "-") == 0)
  {
    if (!_getenv(info, "OLDPWD="))
    {
      _puts(s);
      _putchar('\n');
      return (1);
    }
    _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
    ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
  }
  /* Otherwise, change to the given directory */
  else
    ret = chdir(info->argv[1]);

  /* If the change failed, print an error */
  if (ret == -1)
  {
    print_error(info, "can't cd to ");
    _eputs(info->argv[1]), _eputchar('\n');
  }
  /* Otherwise, update the environment variables */
  else
  {
    _setenv(info, "OLDPWD", _getenv(info, "PWD="));
    _setenv(info, "PWD", getcwd(buffer, 1024));
  }

  return (0);
}

/* Display help information for built-in commands */
int _myhelp(info_t *info)
{
  char **args;

  args = info->argv;
  
  /* TODO: implement help functionality */

  _puts("help call works. Function not yet implemented \n");

  if (0)
    _puts(*args); /* temp att_unused workaround */

  return (0);
}
