import asyncio
import httpx
import jwt

transactions = [
    {"user_id": 101, "amount": 250.0, "merchant": "Amazon"},
    {"user_id": 102, "amount": 50.0, "merchant": "Starbucks"},
    {"user_id": 103, "amount": 1000.0, "merchant": "Apple"}
]

async def call_microservice(transaction):
    env_file = ".env.kong" 
    with open(env_file) as f:
        env_vars = dict(line.strip().split('=') for line in f if line.strip() and not line.startswith('#'))
    payload = {"iss": env_vars["JWT_KEY"]}
    print (f"Generated JWT payload: {payload}")
    token = jwt.encode(payload, env_vars["JWT_SECRET"], algorithm=env_vars["JWT_ALGORITHM"])
    print (f"Generated JWT token: {token}")
    headers = { "Authorization": f"Bearer {token}" }
    async with httpx.AsyncClient() as client:
        client.headers.update(headers)
        response = await client.post("http://localhost:8000/predict", json=transaction)
        return response.json()

async def main():
    tasks = [call_microservice(tx) for tx in transactions]
    results = await asyncio.gather(*tasks)
    for res in results:
        print(res)

if __name__ == "__main__":
    asyncio.run(main())