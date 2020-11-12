

## Protocole

| Client     | Server      | Détails                                                           |
|------------|-------------|-------------------------------------------------------------------|
| CONNECT    |             |                                                                   |
|            | CONNECTED   | (adversaire, balance initiale,                                    |
|            | FAILED      | Quand username != server_config                                   |
|            | ROUND_START | (Envoie simultané aux deux clients : current_round, délai de jeu) |
| ACTION     |             | (mise, action, tmps réaction)                                     |
|            | ROUND_END   | Envoie des résultats (vainqueur, perdant)                         |
|            | GAME_END    | (round == maxRound \|\| balance == 0)                             |
|            | DISCONNECT  |                                                                   |
| DISCONNECT |             |                                                                   |



