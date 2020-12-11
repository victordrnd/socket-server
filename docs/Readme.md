# Développement

## Debug
Il est possible de désactiver le mode __DEBUG__ sur le serveur et le client en ajoutant **-DNDEBUG** lors de la compilation.

Dans le *Makefile* modifié la ligne comme ceci :

`CFLAGS	:= -Wall -Wextra -g -std=c11 -DNDEBUG`


## Protocole

| Code | Client     | Server      | Détails                                                           |
|------|------------|-------------|-------------------------------------------------------------------|
|  16  | CONNECT    |             | *void*                                                            |
|  17  |            | CONNECTED   | *Connected_data*                                                  |
|  18  |            | FAILED      | *void*                                                            |
|  19  |            | GAME_START  | *Game_Start_data*                                                 |
|  20  |            | ROUND_START | *Round_Start_data*                                                |
|  21  | ACTION     |             | *Game*                                                            |
|  22  |            | ROUND_END   | *Game*                                                            |
|  23  |            | GAME_END    | *Game_End_data*                                                   |
|  24  | DISCONNECT |             | *void*                                                            |


```C
enum verbs{
    CONNECT = 0x10U, //Offset de 16 car 0-16 réservé pour les actions (collaborate, betray)
    CONNECTED = 0x11U,
    FAILED = 0x12U,
    GAME_START = 0x13U,
    ROUND_START = 0x14U,
    ACTION = 0x15U,
    ROUND_END = 0x16U,
    GAME_END = 0x17U,
    DISCONNECT = 0x18U
};

typedef struct {
    __uint32_t sender_id;         
    __uint32_t destination_id;
    __uint64_t timestamp;
    __uint32_t action;  //enum verbs
    __uint64_t sizeof_data;
    __uint8_t data[MAXPACKETSIZE];
} __attribute__((packed)) Encapsulation;


```

## Structures échangées 

### Connected_data

```C
typedef struct{
    __uint32_t opponent_id;
    __uint32_t initial_balance;
} Connected_data;
```

### Game_Start_data

```C
typedef struct {
    __uint32_t max_rounds;
    __uint32_t initial_balance;
} Game_Start_data;
```

### Round_start_data

```C
typedef struct {
    __uint32_t waiting_time; //Durée d'attente avant de commencer le round
} Round_Start_data;
```

### Game_End_data

```C
typedef struct {
    __uint32_t result;
} Game_End_data;
```

L'attribut result est un membre de l'énumération suivante

```C
enum results {
    VICTORY = 0x20U,
    DEFEAT = 0x21U,
    EQUALITY = 0x22U
};
```


