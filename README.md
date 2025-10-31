Connexions nécessaires

MAX30100 → Arduino
VIN     → 3.3V ou 5V
GND     → GND
SDA     → A4 
SCL     → A5 
Comment visionner les informations lues par le capteur ?

Option 1 : Moniteur Série Arduino (Le plus simple)

1-Ouvrez l'IDE Arduino
2-Uploadez le code sur votre Arduino
3-Cliquez sur l'icône du moniteur serie en haut à droite (ou Ctrl+Shift+M)
4-Vérifiez que le débit est à 115200 bauds (en bas à droite)
5-Placez votre doigt sur le capteur
Vous verrez :
✓ Capteur MAX30100 détecté!
Signal IR brut: 15234
BPM:72 SPO2:98
┌─────────────────────────────────┐
│ Fréquence cardiaque: 72 BPM    │
│ SpO2 (Oxygène):      98 %       │
└─────────────────────────────────┘
💓 Battement détecté!
Option 2 : Interface Web Graphique (Recommandé)

Étape 1 : Télécharger le fichier "Interface Graphique"
1. Copiez le code HTML de l'interface que j'ai créé
2. Créez un fichier nommé "Moniteur_Cardiaque.html"
3. Collez le code et sauvegardez

Étape 2 : Utiliser l'interface
Gardez l'Arduino branché en USB avec le code uploadé
2. Ouvrez "Moniteur_Cardiaque.html" dans votre navigateur 
3. Cliquez sur "📡 Connecter au Port Série"
4. Sélectionnez votre port Arduino (ex: COM3, COM4)
5. Placez votre doigt sur le capteur

Vous verrez :
- ✅ Cartes colorées avec BPM et SpO2 en grand
- 📊 Graphique en temps réel de votre rythme cardiaque
- ❤️ Animation du cœur qui bat
NB: le moniteur serie et l'interface graphique ne peuvent pas etre utiliser au meme moment 












