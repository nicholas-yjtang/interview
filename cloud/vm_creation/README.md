# Task
To perform automated configuration for up to 100 VMs/containers

# Solution
To perform this task, we propose using terraform you can import the ID via csv

```terraform
locals {
  csv_data= file("${path.module}/users.csv")
  users = csvdecode(local.csv_data)
}
```

Using cloud-init, we can create the user and add the public key to the authorized_keys file

```terraform
resource "azurerm_virtual_machine" "vm" {
  count = length(locals.users)
  ...

  # Use Cloud-init to configure the VM
  user_data = <<-EOF
    #cloud-config
    users:
      - name: ${locals.users[count.index].username}
        ssh-authorized-keys:
          - "${file("~/.ssh/ssh_keys/${count.index}.pub")}"
        sudo: ["ALL=(ALL) NOPASSWD:ALL"]
    EOF

}
```

For a sample of how to do this, go to https://github.com/nicholas-yjtang/scripts/tree/main/terraform/vm_creation