#include "minishell.h"
char *read_line(t_config *config)
{
  char *line;
  line = readline(config->banner);
  if (line == NULL)
    return (0);
  else
    add_history(line);
    return (line);
}

void cmd_fill(t_config *config){
    char **cmdf;
    char **tmp1;
    int i;
    int j;

    j = 0;
    i = 0;
    config->cmd_counter = 0;
    config->args_counter = 0;

    cmdf = ft_split(config->line,(char)PIPE_DELM);

    while(cmdf[i]){
        tmp1 = ft_split(cmdf[i],(char)SPACE_DELM);

        while(tmp1[j]){
            if(j % 2 == 0){
                //printf("cmdf id %d : %s \n", config->cmd_counter, tmp1[j]);
                config->cmd[config->cmd_counter] = tmp1[j];
                config->cmd_counter++;
            }
            else{
                //printf("args id %d : %s \n", config->args_counter, tmp1[j]);
                config->args[config->args_counter] = tmp1[j];
                config->args_counter++;
            }
            j++;
        }
        tmp1 = 0;
        j = 0;
        i++;
    }
}

int cmd_parser(t_config *config){
    char **cmd;
    char **tmp;
    int i;
    i = 0;
    config->cmd_counter = 0;
    config->args_counter = 0;
    if(operator_detector(config->line, "|")){
        printf("pip here \n");
        cmd = ft_split(config->line,(char)PIPE_DELM);
        while(cmd[i]){
            tmp = ft_split(cmd[i],(char)SPACE_DELM);
            config->cmd_counter += ft_strlen(tmp[0]);
            config->args_counter += ft_strlen(tmp[1]);
            i++;
        }
        config->cmd = malloc(sizeof(char *) * config->cmd_counter + 1);
        config->args = malloc(sizeof(char *) * config->args_counter + 1);
        cmd_fill(config);
    }
    else if(operator_detector(config->line, ">")){
        printf("single > here \n");
    }
    else {
        printf("simple cmd \n");
        /*
        tmp = ft_split(config->line,(char)SPACE_DELM);
        //printf("deb : %s \n", tmp[0]);
        if(tmp[0]){
        config->cmd_counter += ft_strlen(tmp[0]);
        config->cmd = malloc(sizeof(char *) * config->cmd_counter + 1);
        }
        if(tmp[1]){
        config->args_counter += ft_strlen(tmp[1]);
        config->args = malloc(sizeof(char *) * config->args_counter + 1);
        }
        //cmd_fill(config);   
        */     
      
    }
return(1);
}

void shell_loop(t_config *config)
{  
  int status;
  status = 1;

  while(status) 
  {
    config->line = read_line(config);
	  if(cmd_parser(config)){
    status = cmd_prexec(config);
    }
	
    
    //free(config->line);
    //free(args);
  }
}

int cmd_prexec(t_config *config)
{
	int i;
	i = 0;
	if (config->cmd[0] == NULL) {
    return 1;
  }
  while(i < config->builtin_len){
      if (ft_strcmp(config->cmd[0], config->builtin_cmd[i]) == 0) {
        return (builtin_func(config->builtin_cmd[i], config->args));
    }
	i++;
  }
return cmd_execute(config);
}
int cmd_execute(t_config *config){

	pid_t pid;

	pid = fork();
	if(pid == 0) {
      if(execve(ft_pathfinder(config->cmd[0], config->envp), &config->args[0], config->envp)){
			printf("error exec.\n");
	}
		exit(EXIT_FAILURE);

	}
	else if(pid > 0) {
		wait(NULL);
	}
	return 1;
}

void shell_init(t_config *config, char **envp){
	config->envp = envp;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
  //config->banner = ft_strcat(getenv("USER"), "@minishell>");
  config->banner = "@minishell>";
  config->n_pipe = 0;
	
}

int main(int argc, char **argv,char **envp)
{
  (void)argc;
  (void)argv;
	t_config config;
	shell_init(&config, envp);
	shell_loop(&config);
  return (1);
}