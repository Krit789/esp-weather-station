import {Prisma, PrismaClient} from "@prisma/client";
import {DateTime} from "luxon";

export default defineEventHandler(async () => {
    const prisma = new PrismaClient();
    const sensor_data = await prisma.sensor_data.findMany({
        where: {
            time: {
                gte: DateTime.now().minus({hours: 6}).toJSDate(),
                lte: DateTime.now().toJSDate(),
            },
        },
    });
    return {
        status: 1,
        message: sensor_data,
    };
});
