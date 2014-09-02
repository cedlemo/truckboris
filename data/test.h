#ifndef DEF_TEST_H
#define DEF_TEST_H
struct ana {
  int touf;
} nas;

struct _geronimo {
  double b;  
};

struct {
  char * titi;
  float y;
} pomme;

typedef int toto;

//typedef struct _geronimo indien;


typedef struct {
  char z;
} tomate;

struct _poire {
  int g;
  tomate rouge;
};
typedef struct _poire kudamono;

struct {
  int zozo;
  kudamono fruit;
} poney;

typedef struct poney equide;
#define TOTO 20
//indien c;
int a= 3;
void une_fonction(int arg1, double arg2);
enum strategy { RANDOM, IMMEDIATE, SEARCH };
enum strategy my_strategy = IMMEDIATE;
typedef enum pipete { CANON, FUSIL = 3, ARC, CANNEAPECHE } aplume;
typedef enum { POLO, MARCO, NADINE } baka;
void pupute(tomate *, const equide *);
union Data
{
   int i;
   float f;
   char  str[20];
};
typedef kudamono tabemono;
#endif //DEF_TEST_H
