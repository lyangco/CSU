int process(char *ch[])
{
	pid_t ch_pid;
	int status;
	ext int status;
	
	if (ch_pid == 0)
	{
		if (execvp(ch[0], args) == -1)
		{
			perror("Failed Fork");
			return 1;
		}
		exit(0);
	}
	else if (ch_pid < 0)
	{
		perror("Failed Fork");
	}
	else
	{
		do{
			w_pid = waitpid(ch_pid, status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}
