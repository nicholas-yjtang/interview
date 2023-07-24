# Problem

You are working in an educational instituitio that would like to provide a platform for students and teachers to create their own websites. The school has a Kubernetes cluster that is managed by your department which you can utilize for this. How would you go about designing a solution for this?

You may make assumptions on the scenario of the usage (whether it is for a particular class, or it is for the entire school, how many users, for how long etc), but please state your assumptions clearly.

# Solution

## Assumptions

We make the assumption that this is for a particular class or module in the school (Web Application Development 101). 

This particular class will have no more than 100 students, and the teachers will also use this to demonstrate how to create a website. The course will last for 3 months at a time, and the students will be given access only during the course duration. Expect new students to join the course every 3 months.

We assume the goal of this course is to create a website/web application that will be finally deployed for the student's final evaluation. In between they are allowed to deploy their websites for testing purposes. The students will be graded based on the website/web application that they have created.

We will also assume that the students have some knowledge on deploying pods, are able to package their website/web application into a docker image, and push it to a container registry. 

## Design

![Architecture Diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/nicholas-yjtang/interview/main/cloud/kubernetes1/diagrams/architecture_design.puml)

The design of this solution is broken down into mainly 3 parts:

1. The user authentication sync process
2. The upload to a container registry process
3. The service sync process

### User Authentication Sync Process

Since the students are basically transiet users (only for 3 months), it makes sense that we should perform some kind of automation to allow these particular students of the module to access the cluster. Outright allowing all students to access it would be a security risk, and would also be a waste of resources, but to keep track of the students that are taking the module, and manually create their accounts would be a waste of time.

We assume some kind of information related to the modules they are taking are stored in the school's user directory (LDAP, Active Directory etc),

In order to sync this LDAP information, we will nornally need to create a custom controller that will sync the users from the school's user directory to the Kubernetes cluster, but in this case we will simplify this by instead using a python application that uses the kubernetes library to perform this task

This python application will be running as a pod in the Kubernetes cluster, and will be scheduled to run as a cronjob. The cronjob will run every 5 minutes to ensure that the users are synced to the Kubernetes cluster.

### Upload to a container registry process

Although it is possible to simply use dockerhub.io as the container registry, we take into account the possibility of unknown costs (internet bandwidth from constaint uploading and downloading of the docker images) and security concerns (dockerhub.io is a public container registry, and we do not want to expose the student's work to the public).

In this scenario, the students are expected to
1. Create their own docker images
2. Push their docker images to the private container registry

### Service Sync Process

In order for the students (and public) to access their website, the kubernetes cluster will need to expose the services via a LoadBalancer. This loadbalancer is normally in a form of an IP address that is accessible, but it is not intuitive for the students to remember the IP address. 

In order to simply this, we make make the following assumptions
1. The students have their own unique ID (for example STUDENT001, STUDENT002 etc)
2. The school has a domain name (for example, school.edu.sg)
3. The students will be able to access their website via the following URL: http://STUDENT001.school.edu.sg

In order to achieve this, we will utilize a kubernetes ingress controller to route the traffic to the correct service. The ingress controller will be configured to route the traffic based on the student's ID.

Since we alow the students themselves to deploy the applications (a simple deployment yaml), we would want to watch the service exposed by their deployment, and automatically create the ingress resource for them. This can be done via a python application that will be running as a pod in the Kubernetes cluster. 

We may optionally force the students to only use a specific namespace (for example, STUDENT001), and only allow them to create deployments in that namespace.

## Other concerns

### Security
We can utlize pod security policies to ensure that the containers are running with the least privileges. We can also utilize network policies to ensure that only the necessary ports are open.

### Monitoring

We can utilize kubernetes monitoring tools such as prometheus and grafana to monitor the health and performance of the containers.

We can use tools to log and monitor the network traffic to and from the containers (such as ELK stack), and have users install logging agents in their containers

### Resource Control

Since we are controlling the access to the cluster via the user authentication sync process, we can also control the resources that the students can use. We can use resource quotas to limit the amount of resources that the students can use.