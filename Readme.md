# ICS - Dilemme du prisonnier

## Contexte 
L’ICS (institue of Cognitives Sciences) est un laboratoire interdisciplinaire qui intègre l'expertise de
chercheurs des Sciences de la Vie (psychologie cognitive, neurosciences) et de médecine (pédopsychiatrie, neuro-pediatrie) avec celle de chercheurs des Sciences Humaines et Sociales
(linguistique computationelle et théorique et philosophie) pour étudier la nature et la spécificité de
l'esprit humain. 

Le doctorant, qui n’est pas un développeur, a besoin d’accumuler des données expérimentales. Il a
besoin que des volontaires jouent l’un contre l’autre un nombre de fois à définir, sans jamais savoir
qui sont leurs adversaires.
On définira une partie comme étant un certain nombre de rounds. Un round est défini comme une
confrontation trahison-collaboration entre les deux volontaires.

<h1 align="center">
    <img src="https://i.postimg.cc/523HnPsr/Capture-d-cran-du-2020-11-17-17-20-52.png" />
</h1>


---
# Documentation
### 1. Installation
- [Dépendances](#dépendances)
- [Comment l'utiliser](#how-to-use)

### 2. Configuration
- [Serveur](#configuration-serveur)
- [Client](#configuration-client)
  
### 2. Développement
- [Debug](#debug)
- [Protocole](#protocole)
## Installation 

### Dépendances

Ce projet est dépendant de la librairie [libconfig](https://hyperrealm.github.io/libconfig/).
#### Distribution basée sur Ubuntu (Ubuntu, Linux Mint, Elementary, etc)

Exécutez la commande suivante dans un terminal.

`sudo apt install libconfig-dev`
#### Fedora, CentOS

Exécutez la commande suivante dans un terminal.

`dnf install libconfig-devel`

### How to use

Exécutez la commande suivante dans un terminal.

```bash
# Clonez le dépot Github 
$ git clone https://github.com/victordrnd/socket-server.git

# Aller vers le répertoire
$ cd socket-server

# Compiler le projet (make all, make server, make client)
$ make all

# Executer le serveur/client
$ ./output/server
$ ./output/client

```


## Configuration

### Configuration serveur
La configuration du serveur se trouve dans le fichier `output/config/server_config.cfg` une fois le serveur compilé.

```cfg
bind_ip = "0.0.0.0";
bind_port = 7799;
max_simultaneous_connection = 50;

game_configuration =
(
  {
    name = "room_1";
    initial_amount = 50;
    nb_games = 10;
    clients = (
      {client_id = 1;},
      {client_id = 2;}
    );
  },
  {
    name = "room_2";
    initial_amount = 50;
    nb_games = 10;
    clients = (
      {client_id = 3;},
      {client_id = 4;}
    );
  }
);
```

### Configuration client
La configuration du serveur se trouve dans le fichier `output/config/client_config.cfg` une fois le client compilé.

```cfg
client_id = 1;
server_ip = "127.0.0.1";
server_port = 7799;
```


# Développement

## Debug
Il est possible d'activer le mode __DEBUG__ sur le serveur et le client en ajoutant **-DNDEBUG** lors de la compilation.

Dans le *Makefile* modifié la ligne comme ceci :

`CFLAGS	:= -Wall -Wextra -g -std=c99 -DNDEBUG`


## Protocole

| Code | Client     | Server      | Détails                                                           |
|------|------------|-------------|-------------------------------------------------------------------|
|  16  | CONNECT    |             |                                                                   |
|  17  |            | CONNECTED   | *Connected_data* : (balance initiale, adversaire_id)              |
|  18  |            | FAILED      | L'utilisateur n'est pas présent dans la configuration serveur     |
|  19  |            | GAME_START  | Max round count                                                   |
|  20  |            | ROUND_START | (Envoie simultané aux deux clients : current_round, délai de jeu) |
|  21  | ACTION     |             | (mise, action, tmps réaction)                                     |
|  22  |            | ROUND_END   | Envoie des résultats (vainqueur, perdant)                         |
|  23  |            | GAME_END    | (round == maxRound \|\| balance == 0)                             |
|  24  |            | DISCONNECT  |                                                                   |
|  24  | DISCONNECT |             |                                                                   |



