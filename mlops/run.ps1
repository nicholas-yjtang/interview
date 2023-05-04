$convert_id = docker ps -f name=convert-app --format "{{.ID}}"
$convert_port = ((docker port $convert_id) | select-string -Pattern "0.0.0.0" | out-string).Trim().Split(":")[1]
$form_notebook=@{file=(Get-Item iris.ipynb)}
$convert_output=Invoke-RestMethod -Uri http://localhost:$convert_port/convert -Method Post -Form $form_notebook -ContentType 'multipart/formdata'
$model_name = $convert_output.model_name
Write-Host "model_name: $model_name"
Invoke-WebRequest -Uri "http://localhost:$convert_port/model?model_name=$model_name" -OutFile model.pkl
$predict_id = docker ps -f name=predict-app --format "{{.ID}}"
$predict_port = ((docker port $predict_id) | select-string -Pattern "0.0.0.0" | out-string).Trim().Split(":")[1]
$form_model=@{file=(Get-Item model.pkl)}
Invoke-WebRequest -Uri "http://localhost:$predict_port/model" -Method PUT -Form $form_model -ContentType 'multipart/form-data'
$webapp_id = docker ps -f name=web-app --format "{{.ID}}"
$webapp_port = ((docker port $webapp_id) | select-string -Pattern "0.0.0.0" | out-string).Trim().Split(":")[1]
Invoke-RestMethod -Uri "http://localhost:$webapp_port/predict" -Method POST -Body '{"sepal_length": 5.1, "sepal_width": 3.5, "petal_length": 1.4, "petal_width": 0.2}' -ContentType "application/json"