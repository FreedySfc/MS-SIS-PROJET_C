# Projet C

## Description

Programme en C pour générer et rechercher des condensats (hashs) SHA-256.

Deux modes :  
- **G** : Génère une table (T3C) chaîne → condensat à partir d’un fichier dictionnaire (un mot par ligne).  
- **L** : Recherche la chaîne correspondant à un ou plusieurs condensats donnés, en utilisant une table T3C.

---

## Prérequis

- OS Linux (Debian/Ubuntu recommandé)  
- `gcc`  
- OpenSSL (libssl-dev)

Installer les dépendances :

```bash
sudo apt update
sudo apt install build-essential libssl-dev

Compilation

make    'qui va générer un fichier binaire hash_tool qui va nous permettre de faire nos manipulations'

Utilisation

Mode G (génération)

./hash_tool G <fichier_dictionnaire> <fichier_T3C>

Exemple :

./hash_tool G mdp.txt table.t3c   "se sert du fichier mdp.txt pour générer un autre fichier contenant les chaines;les condensats"

Mode L (recherche)

Lit les condensats (SHA-256 hex) depuis l'entrée standard, un par ligne, et affiche la chaîne correspondante ou [non trouvé].

cat queries.txt | ./hash_tool L table.t3c

ou en mode interactif :

./hash_tool L table.t3c
# taper un condensat, puis Ctrl+D

Format des fichiers

    Dictionnaire (mdp.txt) : une chaîne par ligne (ex: mots de passe).

    Table T3C (table.t3c) : chaque ligne est chaine;condensat_sha256_hex.

Dépannage rapide

    Si #include <openssl/sha.h> est souligné dans VS Code, installe libssl-dev et ajoute les chemins /usr/include et /usr/include/x86_64-linux-gnu dans la configuration IntelliSense (c_cpp_properties.json).

    Si compilation avertit sur strdup, ajoute #define _POSIX_C_SOURCE 200809L en tête de lookup.c.

    Vérifie que les fichiers existent et ont les bonnes permissions.

Exemple de test

Créer un fichier mdp.txt :

azerty
motdepasse
123456

Générer la table :

./hash_tool G mdp.txt table.t3c

Rechercher un condensat (extrait depuis la table) :

grep '^motdepasse;' table.t3c | cut -d';' -f2 | ./hash_tool L table.t3c
