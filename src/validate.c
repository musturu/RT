#include "../include/minirt.h"
#include <unistd.h>


static char	*filetostr(int fd)
{
	int		r;
	char	buf[42];
	char	*join;
	char	*tmp;

	join = ft_strdup("");
	r = 1;
	while (r != 0)
	{
		tmp = join;
		r = read(fd, buf, 20);
		buf[r] = 0;
		join = ft_strjoin(join, buf);
		free(tmp);
	}
	return (join);
}

char	*readfile(int argc, char **argv)
{
	char	*point;
	int		fd;

	if (argc != 2)
		exit(write(2, "Error\nWrong argument count\n", 27));
	point = ft_strrchr(argv[1], '.');
	if (!point || (*(point+1) != 'r' || *(point + 2) != 't' || *(point + 3) != 0))
		exit(write(2, "Error\nWrong file extension!\n", 28));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(write(2, "Error\nCannot open file, sry!\n", 29));
	return (filetostr(fd));
}

