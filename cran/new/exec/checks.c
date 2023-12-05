#include "lumumbash.h"



t_error	ft_check_exec(char *file, bool cmd)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_error){CANT_EXECUTE, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	if (cmd)
		return ((t_error){NOT_FOUND, CMD_NOT_FOUND, file});
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}

t_error	ft_check_read(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}

t_error	ft_check_write(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}
