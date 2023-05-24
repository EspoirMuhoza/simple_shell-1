#include "shell.h"

/**
 * _mycd() - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info) {
  /**
   * Get the current working directory.
   */
  char *s = getcwd(buffer, 1024);
  if (!s) {
    /**
     * TODO: Display an error message if getcwd() fails.
     */
    _puts("TODO: >>getcwd failure emsg here<<\n");
  }

  /**
   * If no directory is specified, change to the user's home directory.
   */
  if (!info->argv[1]) {
    dir = getenv("HOME");
    if (!dir) {
      chdir_ret = chdir("/");
    } else {
      chdir_ret = chdir(dir);
    }
  }

  /**
   * If the directory is "-", change to the previous directory.
   */
  else if (strcmp(info->argv[1], "-") == 0) {
    dir = getenv("OLDPWD");
    if (!dir) {
      _puts(s);
      _putchar('\n');
      return (1);
    }
    _puts(dir);
    _putchar('\n');
    chdir_ret = chdir(dir);
  }

  /**
   * Otherwise, change to the specified directory.
   */
  else {
    chdir_ret = chdir(info->argv[1]);
  }

  /**
   * If chdir() fails, display an error message.
   */
  if (chdir_ret == -1) {
    print_error(info, "can't cd to ");
    _eputs(info->argv[1]), _eputchar('\n');
  }

  /**
   * Set the OLDPWD and PWD environment variables.
   */
  else {
    setenv("OLDPWD", getenv("PWD"), 1);
    setenv("PWD", getcwd(buffer, 1024), 1);
  }

  return (0);
}
