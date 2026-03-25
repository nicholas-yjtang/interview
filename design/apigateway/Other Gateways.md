
Various types of API gateways that comes up during interviews

Draw a simple API Gateway

```mermaid
flowchart TD  
	A[Client / Browser]
    B[API Gateway NGINX]
    C[Service 1 - Flask API]
    D[Service 2 - Flask API]
    A-->|HTTP Request|B
	subgraph Docker Compose Network  	
		B -->|/service1| C 
		C -->|Response| B
		B -->|/service2| D  
		D -->|Response| B
	end    
	B-->|HTTP Response| A
```

Show the flow of services and the logic inside the API gateway

```mermaid
flowchart TD
    client1[Client 1]
    client2[Client 2]
    client3[Client 3]
    servicea[Service A]
    serviceb[Service B]
    servicec[Service C]
    subgraph "API Gateway"
        direction TB
	    A[Process Incoming Request]    
	    B[Run middleware]
	    C[Route to correct service]
	    A -->B
	    B -->C
	end
	client1 -->|/serviceA| A
	client2 -->|/serviceB| A
	client3 -->|/serviceC| A
	C -->|/serviceA| servicea
	C -->|/serviceB| serviceb
	C -->|/serviceC| servicec
	servicea -->|Data Updates|data1[(Database1)]
	serviceb -->|Data Updates|data2[(Database2)]
	servicec -->|Data Updates|data3[(Database3)]
```


Draw an API gateway with some of the different kinds of middle layer you might utilise

```mermaid

flowchart TD  
%% Client  
A[Client Application] -->|HTTPS Request| B[API Gateway]  
  
%% API Gateway Responsibilities  
B --> C[Authentication & Authorization]  
B --> D[Rate Limiting / Throttling]  
B --> E[Caching Layer]  
B --> F[Request Transformation / Routing]  
  
%% Backend Services  
F --> G[Microservice 1]  
F --> H[Microservice 2]  
F --> I[Microservice 3]  


%% Databases & Caches  
G -->|Data Updates| J[(SQL / NoSQL Database)]
H -->|Data Updates| K[(Redis / Memcached)]  
I --> J  

%% Monitoring & Logging  
B --> L[Monitoring & Logging System]  
G --> L  
H --> L  
I --> L  
  
%% Optional Feedback Loop  
L -->|Metrics / Alerts| B

```
