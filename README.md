![Cosmos War logo](resources/img/cosmos-war.png)

###### Illarietti Marco, Pietro Tarenzi - A.S. 2022/2023 I.I.S. Badoni 5BI

### SCOPO DEL PROGETTO
Realizzare un videogioco di combattimento, utilizzando le socket per implementare la funzionalità multigiocatore.

### DESCRIZIONE DEL GIOCO
Cosmos War è un videogioco di combattimento che utilizza le socket per implementare la funzionalità multigiocatore. 
Cosmos War è ambientato nello spazio dove due giocatori assumono il comando delle rispettive navicelle spaziali in conflitto una contro l’altra. 
Oltre ai proiettili vaganti sul campo di battaglia, saranno presenti degli asteroidi che possono risultare un vantaggio per proteggersi dai colpi avversari,
ma anche uno svantaggio per quanto riguarda i movimenti.

### TECNOLOGIE UTILIZZATE
Per realizzare il videogioco abbiamo utilizzato le seguenti tecnologie: 
- Linguaggio di programmazione C e C++ perché più adatti
allo sviluppo di videogiochi e per avere più dimestichezza con le socket, utilizzate per implementare la modalità multiplayer. 
- SDL2 [(Simple DirectMedia Layer)](https://www.libsdl.org/), ovvero una libreria multipiattaforma che permette l’accesso a basso livello all’audio,
alle periferiche e all’hardware grafico tramite OpenGL. 
- Socket UDP, implementandole utilizzato la libreria NetInet e la libreria Arpa.
L’utilizzo di questo tipo di socket è motivato dal fatto che volevamo garantire la minima latenza possibile tra i due giocatori durante il gioco.
- [Pixel Art Maker](https://www.pixilart.com/), un sito online gratuito per realizzare Pixel Art che abbiamo usato per creare le immagini di gioco (navicella o asteroidi) e le scritte.

### COME SI GIOCA
Dopo aver avviato il gioco, premere Il tasto PLAY che ti rimanderà ad una schermata dove bisognerà scegliere se hostare
la partita o accedere ad essa. Una volta scelto in che modo accedere alla partita bisogna inserire l’indirizzo IP dell’host,
ci si ritroverà in una schermata in cui si attenderà che la connessione tra server e client sia stabilità. Dopo aver seguito questi passi,
ci si ritroverà sul campo di combattimento. Per muoversi occorrerà utilizzare W (per andare avanti), A (per andare a sinistra),
D (per andare a destra) e S (per andare indietro). Per scegliere la direzione in cui verrà orientata la navicella bisogna spostare 
il cursore all’interno della finestra. Per sparare bisogna mirare con il cursore a forma di mirino il nemico e fare fuoco con il tasto sinistro del mouse.

### COME FUNZIONANO LE SOCKET
Utilizzando le socket UDP bisogna gestire interamente lo scambio di pacchetti tra server e client. 
Il gioco presenta 4 fasi di scambio dei pacchetti: Viene instaurata la connessione tra server e client:
- Il server rimane in attesa del ricevimento dell’id del client (tramite la primitiva recvfrom un thread, 
in quanto la primitiva utilizzata è bloccante, rimane in attesa del ricevimento di un int contenente l’id del client), 
poi ha sua volta invia (tramite la primitiva sendto) il proprio id al client (utilizzando l’IP e la porta da cui è arrivato l’id).
Il client dopo aver inviato il proprio id al server (utilizzando l’IP inserito e la porta fissa e prestabilita), rimane in attesa
come il server dell’id di quest’ultimo. Quando entrambi gli host si saranno scambiati i propri id, conosceranno le informazioni e
i requisiti per scambiarsi messaggi, quindi la connessione sarà stabilita. 
- Il server invia le informazioni preliminari al client per creare il campo di gioco. Il server invia la posizione dei 3 asteroidi, in un array di int di 6 elementi 
([0] coordinata x del primo asteroide, [1] coordinata y del primo asteroide, [2] coordinata x del secondo asteroide,
[3] coordinata y del secondo asteroide, [4] coordinata x del terzo asteroide, [5] coordinata y del terzo asteroide).
Il client rimane in attesa come prima dell’arrivo delle coordinate dei 3 asteroidi, contenute in un array di int di 6 elementi
dal quale verranno estratte le informazioni per poi impostare le posizioni dei vari asteroidi.
- Server e client si scambiano le informazioni di gioco. Il server e il client mandano e poi ricevono le informazioni utili al funzionamento e al movimento durante il gioco.
Le informazioni vengono scambiate tramite un array di int di 4 elementi ([0] id del giocatore, [1] l’evento scatenato dal giocatore,
ovvero un intero che identifica il tasto della tastiera o del mouse premuto, [2] la coordinata x del mouse, [3] la coordinata y del mouse).
Queste informazioni vengono poi processate per riprodurre l’azione dell’altro giocatore. Server e client chiudono la connessione.
- Il server e il client al termine della partita o quando uno dei due chiude il gioco chiudono la comunicazione (tramite la primitiva close chiudono la rispettiva datagram socket).

### INSTALLAZIONE E REQUISITI

Prima di poter giocare occorre seguire i seguenti passaggi (N.B. per via delle librerie utilizzate per la gestione delle socket e dei thread
è possibile utilizzare il gioco solamente su distribuzioni basate su UNIX):

- Installare le librerie di SDL: 
> MacOS, aprire il terminale e lanciare i seguenti comandi:
>> - ```she brew install SDL2```
(libreria per gestire la grafica)
>> - ```brew install SDL2_image``` (libreria per gestire le immagini)
>> - ```brew install SDL2_ttf``` (libreria per gestire i font)
>> - ```brew install SDL2_mixer``` (libreria per gestire l’audio)

> Linux, aprite il terminale e installare tramite il proprio packet manager le seguenti librerie:
>> - SDL2 SDL2_image 
>> - SDL2_ttf 
>> - SDL2_mixer 

- Scaricare il progetto.
- Aprire un terminale e entrare nella cartella src del progetto.
- All’interno del terminale lanciare il comando ```make``` per compilare il codice e generare l’eseguibile. 
- Dopo aver generato l’eseguibile lanciare il comando ```./game``` per eseguire il codice.