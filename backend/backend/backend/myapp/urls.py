# ваш_проект/urls.py

from django.urls import path
from .views import control_arduino

urlpatterns = [
    # Другие URL-адреса вашего приложения...
    path('api/control_arduino/', control_arduino, name='control_arduino'),
]
