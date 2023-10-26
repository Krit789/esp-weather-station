import prisma from '../prisma'
import {DateTime} from "luxon";

export default defineEventHandler(async () => {
    const sensor_data = await prisma.sensor_data.findMany({
        where: {
            time: {
                gte: DateTime.now().minus({hours: 6}).toJSDate(),
                lte: DateTime.now().toJSDate(),
            },
        },
        orderBy: {
            time: 'desc'
        },
        take: 600,
    });
    return {
        status: 1,
        message: sensor_data,
    };
});
