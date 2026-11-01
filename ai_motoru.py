import sys
import warnings
import PIL.Image
import google.generativeai as genai
import re # C++ için verileri ayıklamak için

warnings.filterwarnings("ignore")

GOOGLE_API_KEY = "YOUR_GEMINI_API_KEY_HERE"

def analyze_food_legit():
    if len(sys.argv) < 2:
        return

    image_path = sys.argv[1]
    profil_bilgisi = "YOK"
    if len(sys.argv) >= 3:
        profil_bilgisi = " ".join(sys.argv[2:])

    print(f"\n[*] {image_path} yapay zeka motoru ile analiz ediliyor. Lütfen bekleyin...")

    try:
        genai.configure(api_key=GOOGLE_API_KEY)
        uygun_model = None
        for m in genai.list_models():
            if 'generateContent' in m.supported_generation_methods:
                if 'flash' in m.name or 'vision' in m.name:
                    uygun_model = m.name
                    break
        
        if not uygun_model:
            print("[!] Sistem hatası.")
            return
        
        model = genai.GenerativeModel(uygun_model)
        
        prompt = "Bu bir yemek fotoğrafı. Lütfen SADECE şu formatta cevap ver:\nBESIN: [Adı]\nKALORI: [Sayı]\nPROTEIN: [Sayı]\nKARBONHIDRAT: [Sayı]\nYAG: [Sayı]\nNOT: Rakamların yanına kcal veya gr yazma, sadece rakam ver."
        
        if profil_bilgisi == "YOK":
            prompt += "\nSonuna şu notu ekle: '\n---------------------------------------------\n[!] SİSTEM NOTU: Diyet analizi için profil oluşturun.'"
        else:
            prompt += f"\nKullanıcı: {profil_bilgisi}. En sona '\n---------------------------------------------\n>>> YAPAY ZEKA DİYETİSYEN YORUMU <<<' aç ve tavsiye ver."

        img = PIL.Image.open(image_path)
        response = model.generate_content([prompt, img])
        
        text = response.text.strip()
        print("\n---------------------------------------------")
        print(">>> YAPAY ZEKA BESIN ANALIZ RAPORU <<<")
        print("---------------------------------------------")
        print(text)
        print("---------------------------------------------")

        # --- C++ İÇİN VERİ ÇIKIŞI (KÖPRÜ) ---
        try:
            kalori_match = re.search(r'KALORI:\s*(\d+(\.\d+)?)', text)
            besin_match = re.search(r'BESIN:\s*(.*)', text)
            kal = float(kalori_match.group(1)) if kalori_match else 0
            ad = besin_match.group(1).strip() if besin_match else "Bilinmeyen Besin"
            
            with open("ai_veri.txt", "w", encoding="utf-8") as f:
                f.write(f"{ad}\n{kal}\n")
        except:
            with open("ai_veri.txt", "w", encoding="utf-8") as f:
                f.write("Bilinmeyen\n0\n")

    except Exception as e:
        print(f"\n[!] Hata: {e}")

if __name__ == "__main__":
    analyze_food_legit()