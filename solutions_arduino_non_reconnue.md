Solutions pour Arduino/Diduino non reconnue
===========================================

Ce thread vise à faire le point et apporter des solutions pour les cartes Arduino/Diduino non reconnues par le système d'exploitation. Il sera mis à jour si de nouvelles solutions apparaissent.  
  
Contexte
--------
  
Les cartes Arduino sont souvent équipées d'une puce FTDI. Le modèle 232R ayant un grand succès, la contrefaçon s'y est intéressée.  
FTDI a donc sorti un pilote (version 2.12) sous Windows qui détecte les puces contrefaites, et les "désactive" en reprogrammant le PID (ProductID) de la carte : Concrètement, l'identifiant de la carte sur le port USB est modifié et celle-ci n'est plus reconnue par les pilotes FTDI.  
  
**Comment savoir si la puce FTDI équipant votre carte est contrefaite?**  
  
Sous Windows, dans le gestionnaire de périphériques, vous verrez certainement ceci :  
![ftdi_windows.jpg](https://coursera-forum-screenshots.s3.amazonaws.com/ea/2852f0708511e48238639ea9491fb4/ftdi_windows.jpg)  
  
Sous Linux, ouvrez un terminal et tapez lsusb. Vous devriez trouver une ligne de ce style.  

    Bus 004 Device 003: ID 0403:0000 Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC

Si votre puce FTDI est modifiée, l'ID affiche 0403:0000 au lieu de 0403:6001 pour une originale.  
  
**Solutions**  
  
Suivant votre système d'exploitation, plusieurs solutions sont disponibles.  
- Vous travaillez exclusivement sous Windows.  
- Vous travaillez exclusivement sous Linux ou OSX.  
- Cas particuliers.  
  
  
  
  

### Vous travaillez exclusivement sous Windows.
------------------------------------------------
La solution la plus simple est d'installer le pilote "manuellement" en gardant le PID à 0x0000\. Cette vidéo décrit la procédure:  
[https://www.youtube.com/watch?v=SPdSKT6KdF8](https://www.youtube.com/watch?v=SPdSKT6KdF8)   
La solution fonctionne avec les pilotes FTDI 2.12, mais également avec les 2.10 que vous pouvez télécharger ici:  
32 bits : [http://www.ftdichip.com/Drivers/CDM/CDM%20v2.10.00%20WHQL%20Certified.zip](http://www.ftdichip.com/Drivers/CDM/CDM%20v2.10.00%20WHQL%20Certified.zip)  
64 bits : [http://www.ftdichip.com/Drivers/CDM/CDM%20v2.10.00%20WHQL%20Certified.zip](http://www.ftdichip.com/Drivers/CDM/CDM%20v2.10.00%20WHQL%20Certified.zip)  
  
**Le cas Windows 8/8.1/10 (64 bits, inconnu pour 32 bits)**  
  
A partir de Windows 8, les pilotes font l'objet d'un contrôle accru : Les pilotes non-signés ne sont pas chargés. Pour que la solution proposée fonctionne, ils faut désactiver le contrôle systématique de la signature des pilotes. Ce lien vous sera utile...  
  
[http://www.howtogeek.com/167723/how-to-disable-driver-signature-verification-on-64-bit-windows-8.1-so-that-you-can-install-unsigned-drivers/](http://www.howtogeek.com/167723/how-to-disable-driver-signature-verification-on-64-bit-windows-8.1-so-that-you-can-install-unsigned-drivers/)   
  
Cependant, suivant la façon dont Windows est installé, l'option "Troubleshoot" n'est pas disponible... Et peut-être souhaitez vous garder la sécurité apportée par la vérification systématique des pilotes.  
Une autre solution est donc de reprogrammer la puce, désinstaller les pilotes 2.12 et installer les 2.10\.  
  
  
  
  


### Vous travaillez exclusivement sous Linux ou OS X
-----------------------------------------------------
La solution la plus simple semble être de reprogrammer le PID de la puce FTDI. Le programme ft232r\_prog y arrive très bien.  
  
**Sous Arch**  
  
Sous Arch, ft232r\_prog est disponible depuis AUR. Il suffit d'ouvrir un terminal et de taper:  

    yaourt -S ft232r_prog

Puis vient le moment de reprogrammer le PID. Toujours dans le terminal, entrer:  

    sudo ft232r_prog --old-pid 0x0000 --new-pid 0x6001

Débranchez et rebranchez la carte, si besoin redémarrez.  
Vous pouvez vérifier le succès de l'opération avec lsusb, qui devrait donner:  

    Bus 004 Device 003: ID 0403:6001 Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC

  
  
**Sous Ubuntu**  
  
Ce lien décrit une solution pour Ubuntu.  
[http://forum.arduino.cc/index.php?topic=274387.0](http://forum.arduino.cc/index.php?topic=274387.0)   
Si vous n'êtes pas familier avec git ou n'avez pas de compte github, vous pouvez simplement charger les sources du programme ici:  
[http://www.rtr.ca/ft232r/ft232r\_prog-1.24.tar.gz](http://www.rtr.ca/ft232r/ft232r_prog-1.24.tar.gz)   
Décompressez, puis suivez la procédure depuis cd ft232r\_prog, c'est à dire  

    cd ft232r_prog  
    sudo apt-get install build-essential gcc make libftdi-dev  
    make

puis  

    sudo ./ft232r_prog  --old-pid 0x0000 --new-pid 0x6001

Débrancher puis rebrancher la carte.  
  
  
**Sous OS X**  
  
Installer Macports : [https://www.macports.org/install.php](https://www.macports.org/install.php)  
Dans un terminal, installer libftdi0  

    sudo port install libftdi0

Télécharger les sources de ft232r\_prog : [http://www.rtr.ca/ft232r/ft232r\_prog-1.24.tar.gz](http://www.rtr.ca/ft232r/ft232r_prog-1.24.tar.gz)  
Décompresser l'archive et éditer le makefile, qui doit ressembler à ceci :  

    CFLAGS = -Wall -O2 -s -Werror -I/opt/local/include  
    LDFLAGS =  -L/opt/local/lib -lusb -lftdi -s  
    PROG = ft232r_prog  
      
    all:	$(PROG)  
      
    $(PROG):	$(PROG).c  
    	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)  
      
    clean:  
    	rm -f $(PROG)

Depus le terminal, entrer dans le répertoire de l'archive, et entrer make pour compiler le programme.  
Puis modifier le PID de la puce FTDI :  

    sudo ./ft232r_prog  --old-pid 0x0000 --new-pid 0x6001

Débrancher et rebrancher la carte.  
  
  
  
**Autres solutions**  
  
Patcher le pilote dans le noyau Linux avec le PID 0x0000 et recompiler le noyau....  
  
  
  


### Cas particuliers
--------------------
**Reprogrammer la puce sous Windows et désinstaller les pilotes 2.12\.**  
  
Vous pouvez tenter de reprogrammer la puce sous WIndows avec l'outil Mprog de FTDI. Cette vidéo montre le processus : [https://www.youtube.com/watch?v=RZH\_qGautqM](https://www.youtube.com/watch?v=RZH_qGautqM)   
  
Problème, il est possible que la puce ne soit pas reconnue. Vous pouvez donc passer par Linux pour reprogrammer votre puce.  
  
Puis, une fois reprogrammée, vous pouvez démarrer Windows et brancher la carte qui devrait être reconnue.  
Aller dans le gestionnaire de périphériques, onglet Ports où doit se trouver le port COM associé à la carte (COM 3 ou 4 généralement).  
Clic droit sur le port =\> propriétés =\> onglet pilote =\> désinstaller =\> au passage, cocher la désinstallation du logiciel du pilote.  
Débrancher la carte et redémarrer Windows. Ne rebrancher la carte que lorsque vous êtes sur le bureau.  
Si besoin, installer les pilotes 2.10 disponibles [ici](https://class.coursera.org/microcontroleurs-004/forum/thread?thread_id=180#post-956).
