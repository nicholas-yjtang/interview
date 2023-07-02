# Task
To perform automated configuration for up to 100 VMs/containers

# Solution
To perform this task, we propose using terraform you can import the ID via csv

```terraform
data "csv" "students" {
  source = "students.csv"
}

```

Using cloud-init, we can create the user and add the public key to the authorized_keys file

```terraform
resource "azurerm_virtual_machine" "vm" {
  count = length(data.csv.students.rows)
  ...
  ssh_keys = ["${file("~/.ssh/student_keys/${count.index}.pub")}"]

  # Use Cloud-init to configure the VM
  user_data = <<-EOF
    #cloud-config
    users:
      - name: ${data.csv.students.rows[count.index].student_name}
        ssh-authorized-keys:
          - "${file("~/.ssh/student_keys/${count.index}.pub")}"
        sudo: ["ALL=(ALL) NOPASSWD:ALL"]
    EOF

}
```