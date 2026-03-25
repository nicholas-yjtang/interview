#!/bin/bash
source .env.kong
JWT_TOKEN=$(python -c "import jwt; import os, dotenv; dotenv.load_dotenv('.env.kong'); print(jwt.encode({'iss': os.getenv('JWT_KEY')}, os.getenv('JWT_SECRET'), algorithm=os.getenv('JWT_ALGORITHM')))") 
echo "Generated JWT Token: $JWT_TOKEN"
curl -v -X POST http://localhost:8000/predict \
    -H "Content-Type: application/json" -d '{"user_id": 1, "amount": 100.0, "merchant": "Amazon"}' \
    -H "Authorization: Bearer $JWT_TOKEN"
echo