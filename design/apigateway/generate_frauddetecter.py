from sklearn.ensemble import RandomForestClassifier
import pandas as pd
import joblib
import app.enums

# Create dummy training data
X = pd.DataFrame({
    "user_id": [1, 2, 3, 4, 5],
    "amount": [100.0, 500.0, 10.0, 2000.0, 50.0],
    "merchant": ["Amazon", "Starbucks", "Apple", "Amazon", "Starbucks"]  # encode merchant as integer for simplicity
})
y = [0, 1, 0, 1, 0]  # 0 = not fraud, 1 = fraud

merchant_encoding = app.enums.MERCHANTS
X["merchant"] = X["merchant"].map(merchant_encoding)
# Train model
model = RandomForestClassifier()
model.fit(X, y)

# Save model
joblib.dump(model, "models/fraud_detector_v1.pkl")
print("Model saved as models/fraud_detector_v1.pkl")