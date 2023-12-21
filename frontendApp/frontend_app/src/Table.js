import {Button, Table} from "antd";
import React, {useLayoutEffect, useState} from "react";


function UsersTable() {

    const [dataTable, setDataTable] = useState([]);
    const columnsForAdminUsers = [
        {
            title: 'name',
            dataIndex: ['name']
        },
        {
            title: 'surname',
            dataIndex: ['surname']
        },
        {
            title: 'email',
            dataIndex: ['email']
        },
        {
            title: 'id',
            dataIndex: ['user_id']
        },
        {
            title: 'token',
            dataIndex: ['token']
        },

    ]

    useLayoutEffect(() => {
        const FetchFunction = async () => {
            const res = await fetch("http://localhost:8080/user", {method: "GET"});
            const data = await res.json()
            setDataTable(data);
        }
        FetchFunction();
    }, []);

    return (
        <>
            <div
                style={{
                    fontSize: 20,
                    color: "black",
                }}
            >
                Users table
            </div>
            <Table
                style={{}}
                columns={columnsForAdminUsers}
                dataSource={dataTable}

            />
        </>
    )
}

export default UsersTable