import prisma from '../prisma'
import {DateTime} from "luxon";

export default defineEventHandler(async () => {
    const sensor_data = await prisma.sensor_data.findMany({
        orderBy: {
            time: 'desc'
        },
        take: 1,
    });
    return {
        status: 1,
        message: sensor_data[0],
    };
});
