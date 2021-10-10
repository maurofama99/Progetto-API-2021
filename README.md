# Prova Finale (Progetto di Algoritmi e Strutture Dati) A.A. 2020/21
Il progetto di Algoritmi e Strutture dati consiste nella progettazione e realizzazione di un programma in linguaggio C a partire da una specifica in linguaggio naturale del suo funzionamento.
La struttura della specifica è pensata affinché il candidato utilizzi le conoscenze acquisite nel corso di Algoritmi e Principi dell'Informatica per realizzare un'implementazione che sia non solo corretta, ma anche con efficienza ottimale.

Il progetto rientra nell’ambito della didattica innovativa; la valutazione viene fatta tramite strumenti usati nelle competizioni delle olimpiadi dell’informatica.
L'obiettivo del progetto è la gestione di una classifica tra grafi diretti pesati. La documentazione della specifica è disponibile al seguente link.

## Implementazione

I grafi vengono forniti in input tramite la loro matrice di adiacenza. Il sistema di memorizzazione dei grafi utilizzato nel programma è il CSR (Compressed Sparse Row), che risulta essere il metodo di memorizzazione più efficente, infatti lo spazio necessario per la memorizzazione è O(n+m) (in cui n è il numero di vertici e m è il numero di archi). Inoltre l'utilizzo di arrays piuttosto che di liste concatenate rende più veloce l'accesso ai dati.

L'algoritmo utilizzato per calcolare la somma dei cammini più brevi tra il nodo 0 e tutti gli altri nodi del grafo è l'algoritmo di Dikstra (complessità O((m+n)log n)), utilizzando arrays dinamici al posto di un Heap per ottenere una maggiore velocità di accesso ai dati, e quindi di calcolo.

La struttura dati utilizzata per implementare la classifica è un Max Heap, che con opportune personalizzazioni nel meccanismo di inserimento, si è rivelato il meotodo più efficente per il sistema.

## Testing
L'implementazione è stata testata e debuggata attraverso [Test Pubblici](https://github.com/) e valutata attraverso test privati da una piattaforma apposita in grado di determinare la memoria occupata e il tempo di esecuzione del programma.
