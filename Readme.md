

## Protocole

| Code | Client     | Server      | Détails                                                           |
|------|------------|-------------|-------------------------------------------------------------------|
|  16  | CONNECT    |             |                                                                   |
|  17  |            | CONNECTED   | (adversaire, balance initiale,                                    |
|  18  |            | FAILED      | Quand username != server_config                                   |
|  19  |            | GAME_START  | Max round count                                                   |
|  20  |            | ROUND_START | (Envoie simultané aux deux clients : current_round, délai de jeu) |
|  21  | ACTION     |             | (mise, action, tmps réaction)                                     |
|  22  |            | ROUND_END   | Envoie des résultats (vainqueur, perdant)                         |
|  23  |            | GAME_END    | (round == maxRound \|\| balance == 0)                             |
|  24  |            | DISCONNECT  |                                                                   |
|  24  | DISCONNECT |             |                                                                   |



