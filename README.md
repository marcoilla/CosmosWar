<img src="resources/img/cosmos-war.png" alt="drawing" width="1000"/>

# Cosmos War - Videogioco di Combattimento Multigiocatore

**Autore:** Illarietti Marco, Pietro Tarenzi  
**Anno Scolastico:** 2022/2023  
**Istituto:** I.I.S. Badoni 5BI

## Descrizione del Gioco

**Cosmos War** è un emozionante videogioco di combattimento ambientato nello spazio, progettato per offrire un'esperienza multigiocatore coinvolgente. In questo gioco, due giocatori prendono il comando delle loro navicelle spaziali e si sfidano in un'epica battaglia nel vuoto cosmico. Oltre ai pericolosi proiettili che solcano lo spazio, gli asteroidi si frappongono come ostacoli e rifugi, creando una dinamica di gioco unica in cui la strategia e la destrezza sono fondamentali.

## Tecnologie Utilizzate

Abbiamo sviluppato **Cosmos War** sfruttando una serie di tecnologie avanzate per garantire un'esperienza di gioco fluida e coinvolgente:

- **Linguaggio di programmazione C e C++**: Questi linguaggi sono stati scelti per la loro idoneità allo sviluppo di videogiochi e per la loro compatibilità con l'implementazione di socket necessarie per la modalità multigiocatore.

- **SDL2 (Simple DirectMedia Layer)**: Abbiamo utilizzato SDL2, una libreria multipiattaforma, per gestire l'accesso a basso livello all'audio, alle periferiche e all'hardware grafico tramite OpenGL.

- **Socket UDP**: Abbiamo implementato le socket UDP utilizzando le librerie NetInet e Arpa. Questa scelta ci ha permesso di garantire una minima latenza tra i due giocatori durante il gioco.

- **Pixel Art Maker**: Abbiamo creato le immagini di gioco, inclusi i modelli delle navicelle spaziali e degli asteroidi, nonché le scritte, utilizzando Pixel Art Maker, un sito online gratuito specializzato in grafica pixel art.

## Come Si Gioca

Per iniziare a giocare a **Cosmos War**, segui questi semplici passaggi:

1. Avvia il gioco e fai clic su "PLAY" per accedere alla schermata di selezione.

2. Scegli se vuoi ospitare una partita o unirti a una partita esistente.

3. Se stai ospitando una partita, inserisci l'indirizzo IP del tuo host. Altrimenti, attendi che l'host accetti la tua connessione.

4. Una volta connessi, ti troverai sul campo di battaglia nello spazio. Usa i tasti W, A, S, e D per muoverti e il cursore del mouse per orientare la tua navicella. Premi il tasto sinistro del mouse per sparare ai nemici.

## Funzionamento delle Socket

Il gioco utilizza le socket UDP per gestire la comunicazione tra server e client. Ecco come funziona:

1. **Connessione Iniziale**: Il server e il client si scambiano gli ID tramite le socket UDP per stabilire una connessione stabile.

2. **Informazioni Preliminari**: Il server invia le coordinate degli asteroidi al client per creare il campo di gioco.

3. **Scambio di Informazioni di Gioco**: Durante il gioco, server e client si scambiano informazioni tramite un array di int, consentendo ai giocatori di muoversi e sparare.

4. **Chiusura della Connessione**: Alla fine della partita o quando un giocatore chiude il gioco, la comunicazione viene chiusa.

## Installazione

Prima di iniziare a giocare a **Cosmos War**, assicurati di seguire questi passaggi:

1. Installa le librerie di SDL2 utilizzando i comandi appropriati per il tuo sistema operativo:

   - **MacOS**:

     ```shell
     brew install SDL2 SDL2_image SDL2_ttf SDL2_mixer
     ```

   - **Linux**:

     ```shell
     sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
     ```

2. Scarica il progetto da GitHub.

     ```shell
     git clone https://github.com/marcoilla/CosmosWar.git
     ```

4. Apri un terminale e naviga nella cartella "src" del progetto.

     ```shell
    cd CosmosWar && cd src
     ```

6. Compila il codice e genera l'eseguibile.

     ```shell
    make
     ```

8. Una volta generato l'eseguibile, avvia il gioco.

    ```shell
	./game
     ```

**Nota:** Il gioco è compatibile solo con distribuzioni basate su UNIX a causa delle librerie utilizzate per la gestione delle socket e dei thread.

Divertiti a esplorare il Cosmo e a combattere le epiche battaglie spaziali in **Cosmos War**!
