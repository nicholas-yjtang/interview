$(document).ready(function() {
    $('#input-form').submit(function(event) {
      event.preventDefault();
      const inputData = {
        sepal_length: parseFloat($('#sepal-length').val()),
        sepal_width: parseFloat($('#sepal-width').val()),
        petal_length: parseFloat($('#petal-length').val()),
        petal_width: parseFloat($('#petal-width').val())
      };
      $.ajax({
        type: 'POST',
        url: '/predict',
        data: JSON.stringify(inputData),
        contentType: 'application/json',
        success: function(response) {
          $('#result').text(`Predicted class: ${response.class} (probability: ${response.probability})`);
        },
        error: function(xhr, status, error) {
          console.error(`Error: ${error}`);
        }
      });
    });
  });