import joblib
import pandas as pd
from app.enums import MERCHANTS

# Load pre-trained ML model
model = joblib.load("models/fraud_detector_v1.pkl")

def predict_transaction(transaction: dict) -> dict:
    if "merchant" in transaction:
        if transaction["merchant"] is not None and not isinstance(transaction["merchant"], (int, float)):
            transaction["merchant"] = MERCHANTS.get(transaction["merchant"], 0)  # default to 0 for unknown merchants
    df = pd.DataFrame([transaction])
    prediction = model.predict(df)[0]
    return {"fraud": bool(prediction)}