import en_core_web_sm
import sys
import json
import os

nlp = en_core_web_sm.load()

def analyze(text):
    doc = nlp(text)
    return [(token.text, token.pos_) for token in doc]

if __name__ == "__main__":
    text = sys.argv[1] if len(sys.argv) > 1 else "Error: No arguments provided"
    result = analyze(text)

    output_path = "output.json"
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(result, f, ensure_ascii=False)
