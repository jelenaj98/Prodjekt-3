# Prosjekt-3

Fofattere:  
*Jelena Jovanovic* og *Marte Kvam*

### Prosjektets innhold
I mappen **final** finner du programmene vi brukte får å simulere baner til planeter i solsystemet. I mappen **perihelion** finner du programmene vi bruker for å simulere pressisjonen til Merkur i perihelion. Filen som heter *b.cpp* bruker ikke-objektorientert kode for å simulere Jorden og Jupiter sine baner rundt Solen.

### Kjøring
Alle python-filene som kan kjøres, bruker man kommandoen ```python3 <filnavn>``` til. For å plotte av planetenes baner rundt Solen, kjører du programmet *SolarSystemPlott_2D.py* for å få et 2D plott, og *SolarSystemPlott_3D.py* for å få 3D plott. I disse python-filene skal du velge hvilke planeter du ønsker å simulere, samt med hvilken metode du ønsker å bruke. *SolarSystemPlott_Energy.py* bruker du når du skal plotte den kinetiske, potensielle og totale energien til systemet ditt. Her igjen velger du selv hvilke planeter systemet ditt består av.

I *main.cpp* kan man legge til planeter og velge hvilken algoritme man ønsker å bruke. For å kjøre *main.cpp*, kjører man kommandoene ```g++ -o main.exe main.cpp planet.cpp solarsystem.cpp -larmadillo``` for å kompilere, og deretter ```./main.exe``` for å eksekvere hovedprogrammet.

For å kjøre oppgave i, har vi laget egne filer. Disse finner man i mappen **Perihelion**. For å kjøre denne, kjør ```make``` i terminalen når du er i denne mappen. Hvis du ikke har ```make run_perihelion``` installert, kan du kjøre kommandoene i *Makefile* etter hverandre.




