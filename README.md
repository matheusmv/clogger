# clogger

simple error messaging and logging system in C

<img src="./assets/d5573229d2e417af1bf3994794c8960d21426293bdeb8832f38257eaacc4b3e8.png" width=100%>

## How to use?

### Console

 - *to activate colors compile with -DLCOLOR*

```C
FILE *file = fopen(file_path, "a");
if (file == NULL) {
        LOG_ERROR("fopen() failed. (%s)", strerror(errno));
        exit(EXIT_FAILURE);
}
```

### File

```C
LOG_ERROR_F("logs/errors.txt", "some crazy shit happened!!!. (%s)", cause);
```
