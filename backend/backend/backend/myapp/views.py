from django.views.decorators.csrf import csrf_exempt
from django.http import JsonResponse

import serial  # импортируем библиотеку для работы с последовательным портом

# Определяем объект последовательного порта для Arduino
ser = serial.Serial('/dev/cu.usbserial-1130', 9600)  # укажите правильный COM-порт и скорость соединения

import json

@csrf_exempt
def control_arduino(request):
    if request.method == 'POST':
        body_unicode = request.body.decode('utf-8')
        data = json.loads(body_unicode).get('data')  # получаем данные из JSON-запроса
        if data:
            # Отправляем данные на Arduino
            ser.write(data.encode())
            return JsonResponse({'success': True, 'message': 'Data sent to Arduino'})
        else:
            return JsonResponse({'success': False, 'error': 'No data provided'})
    else:
        return JsonResponse({'success': False, 'error': 'Only POST requests are allowed'})
