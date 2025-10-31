/*
 * Test du capteur MAX30100
 * Mesure de la fréquence cardiaque et du niveau d'oxygène (SpO2)
 * Bibliothèque: MAX30100lib par OXullo
 */

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

// Callback pour la détection de battement
void onBeatDetected() {
  Serial.println("💓 Battement détecté!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initialisation du MAX30100...");
  
  // Initialisation du capteur
  if (!pox.begin()) {
    Serial.println("ERREUR: MAX30100 non détecté!");
    Serial.println("Vérifiez:");
    Serial.println("- Les connexions I2C (SDA/SCL)");
    Serial.println("- L'alimentation (3.3V)");
    Serial.println("- Les résistances pull-up sur SDA/SCL");
    while (1);
  }
  
  Serial.println("✓ Capteur MAX30100 détecté!");
  
  // Configuration du capteur
  pox.setIRLedCurrent(MAX30100_LED_CURR_24MA);
  
  // Enregistrer le callback pour les battements
  pox.setOnBeatDetectedCallback(onBeatDetected);
  
  Serial.println("\n=== Placez votre doigt sur le capteur ===");
  Serial.println("Appuyez fermement mais sans écraser");
  Serial.println("Attendez 10-15 secondes pour stabilisation");
  Serial.println();
}

void loop() {
  // Mise à jour des lectures du capteur
  pox.update();
  
  // Affichage périodique des valeurs
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    uint8_t spo2 = pox.getSpO2();
    
    Serial.println("┌─────────────────────────────────┐");
    
    // Affichage de la fréquence cardiaque
    Serial.print("│ Fréquence cardiaque: ");
    if (heartRate > 0) {
      Serial.print((int)heartRate);
      Serial.print(" BPM");
      
      // Indicateur de condition
      if (heartRate < 60) {
        Serial.println(" ⬇️  │");
      } else if (heartRate > 100) {
        Serial.println(" ⬆️  │");
      } else {
        Serial.println(" ✓   │");
      }
    } else {
      Serial.println("-- BPM      │");
    }
    
    // Affichage du SpO2
    Serial.print("│ SpO2 (Oxygène):      ");
    if (spo2 > 0) {
      Serial.print(spo2);
      Serial.print(" %");
      
      // Indicateur de niveau d'oxygène
      if (spo2 >= 95) {
        Serial.println("  ✓   │");
      } else if (spo2 >= 90) {
        Serial.println("  ⚠️  │");
      } else {
        Serial.println("  ❌  │");
      }
    } else {
      Serial.println("-- %        │");
    }
    
    Serial.println("└─────────────────────────────────┘");
    
    // Conseils si pas de lecture
    if (heartRate == 0 && spo2 == 0) {
      Serial.println("⚠️  Aucun doigt détecté ou signal faible");
      Serial.println("   → Repositionnez votre doigt");
      Serial.println("   → Appuyez plus fermement");
    }

    // >>> LIGNE AJOUTÉE POUR L’INTERFACE WEB (format simple lisible par ton HTML/JS) <<<
    // N'envoie la ligne que si les deux valeurs sont valides (>0)
    if (heartRate > 0 && spo2 > 0) {
      Serial.print("BPM:");
      Serial.print((int)heartRate);
      Serial.print(" SPO2:");
      Serial.println((int)spo2);  // fin de ligne \n indispensable
    }
    // <<< FIN AJOUT >>>

    Serial.println();
    
    tsLastReport = millis();
  }
}
