# Task
In this task we would like to propose a solution for users to create their own websites

# Solution
Since we are unsure how would users go about creating their own website (whether it is simply using wordpress or creating their own custom sites using nodejs, python, etc), we would like to propose using containers to allow users to create their own websites.

In this scenario, users are expected to
1. Create their own docker images
2. Push their docker images to a container registry defined by the administrators

The administrator would then create a container group using the docker image provided by the user on the Kubernetes cluster.

## Security

We can utlize pod security policies to ensure that the containers are running with the least privileges. We can also utilize network policies to ensure that only the necessary ports are open.

## Monitoring

We can utilize kubernetes monitoring tools such as prometheus and grafana to monitor the health and performance of the containers.

We can use tools to log and monitor the network traffic to and from the containers (such as ELK stack), and have users install logging agents in their containers

## Resource Control

We can utilize kubernetes resource quotas to ensure that users do not exceed their resource limits.