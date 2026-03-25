from fastapi import FastAPI, HTTPException
from app.models import Transaction
from app.services import predict_transaction

app = FastAPI(title="Fraud Detection Service")

@app.post("/predict")
async def predict(transaction: Transaction):
    try:
        result = predict_transaction(transaction.dict())
        return {"user_id": transaction.user_id, **result}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))