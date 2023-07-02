# Task
Propose a solution to the following problem

Create and manage up to 100 VM/containers

# Solution

In general I would propose using Azure platform for this task. It provides a lot of tools for managing VMs and containers. It also provides a lot of tools for monitoring and scaling.

## Self service portal

We can utilize the current azure portal to create and manage VMs and containers. We will utilize ARM (Azure Resource Manager) templates to create VMs and containers. We can provide a predefined set of templates for users to choose from

## Resource Control

We can utilize Azure Resource Manager Policies to control the resources that users can create, and to also enforce certain resource limits and quotas to ensure that users do not exceed their limits.

There are also Azure Management Groups and RBAC (Role Based Access Control) that can be used to control access to resources.

## Security

Azure has Network Security Groups that can be used to control network traffic to and from VMs and containers, so we can ensure that only the necessary ports are open.

We can also utilize Azure Security Center to monitor and manage security of VMs and containers.

## Identity Management

We can utilize Azure Active Directory to manage users and groups, and to control access to resources. 

## Monitoring

We can utilize Azure Monitor to monitor the health of VMs and containers, and to also monitor the performance of VMs and containers. You can set up alerts to notify you when certain thresholds are reached.

## Maintenance, patching, and updates

We can utilize Azure Update Management to manage updates and patches for VMs and containers. We can also utilize Azure Automation to automate maintenance tasks.