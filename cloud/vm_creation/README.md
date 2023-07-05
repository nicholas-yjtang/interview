# Task
To perform automated configuration for up to 100 VMs/containers

# Solution
To perform this task, we propose using terraform you can import the ID via csv

```terraform
locals {
  csv_data= file("${path.module}/students.csv")
  students = csvdecode(local.csv_data)
}
```

Using cloud-init, we can create the user and add the public key to the authorized_keys file

```terraform
resource "azurerm_virtual_machine" "vm" {
  count = length(locals.students)
  ...
  ssh_keys = ["${file("~/.ssh/student_keys/${count.index}.pub")}"]

  # Use Cloud-init to configure the VM
  user_data = <<-EOF
    #cloud-config
    users:
      - name: ${locals.students[count.index].student_name}
        ssh-authorized-keys:
          - "${file("~/.ssh/student_keys/${count.index}.pub")}"
        sudo: ["ALL=(ALL) NOPASSWD:ALL"]
    EOF

}
```