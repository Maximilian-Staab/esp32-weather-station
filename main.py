"""
HTTP Server for receiving temperature and humidity data
Used to debug the sensors.
"""

from aiohttp import web
import asyncio

from time import time
from typing import List


OUTPUT = False


class WeatherData:
    def __init__(self, temperature, humidity):
        self.temperature = temperature
        self.humidity = humidity
        self.time = time()


class Controller:
    def __init__(self, ip):
        self.data: List[WeatherData] = []
        self.ip = ip
        self.name = str(ip)


async def get_new_data(request):
    body = await request.json()
    if OUTPUT:
        print(request, request.remote, body)
    try:
        request.app['data'][request.remote].data.addend(
            WeatherData(body['temp'], body['hum']))
    except KeyError:
        request.app['data'][request.remote] = Controller(request.remote)
        request.app['data'][request.remote].data.addend(
            WeatherData(body['temp'], body['hum']))
    return web.Response(text='success')


app = web.Application()
app.add_routes([web.post('/data', get_new_data)])

if __name__ == '__main__':
    web.run_app(app, port=12543)
