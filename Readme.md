

## Protocole

Client          Server

CONNECT
                CONNECTED  (adversaire, balance initiale) || FAILED (qd username != défini dans server_config)
                GAME_START (Configuration Room (current_round + maxRound)
                ROUND_START (Envoie aux deux clients, current_round, délai de jeu)
ACTION
                ROUND_END (résultat qui a gagné)
                ROUND_START
...
                GAME_END (nbRound == maxRound || cagnote == 0)
                DISCONNECT
DISCONNECT



enum verbs  {
    CONNECT = 0,
    CONNECTED = 1,
    ...
}
